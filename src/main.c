/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 14:55:26 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


volatile sig_atomic_t	g_sigint_received = 0;

void	sig_init(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	prompt_init(t_mini *mini, int exit_code)
{
	char		*prompt;

	sig_init();
	configure_terminal();
	while (1)
	{
		g_sigint_received = 0;
		prompt = readline(give_me_prompt(mini));
		if (!prompt)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS) ;
		}
		free(mini->prompt_msg);
		add_history(prompt);
		mini->prompt = prompt;
		mini->exitcode = exit_code;
		parse_init(mini);
		free(prompt);
		prompt = NULL;
		exit_code = mini->exitcode;
	}
	rl_clear_history();
}


void	sigint_handler(int sig)
{
	(void)sig;

	write (1, "\n", 1);
	if (!g_sigint_received && sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	configure_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ECHO | ICANON | ISIG);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	leaks()
{
	system("minishell");
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	int		exit_code;

	exit_code = 0;
	mini.env = dup_env(env);
	prompt_init(&mini, exit_code);
	atexit(leaks);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}
