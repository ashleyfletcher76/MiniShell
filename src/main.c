/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/23 16:29:42 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	sigint_received = 0;

void	sigint_handler(int sig)
{
	(void)sig;

	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	sigint_received = 1;
}

void	sig_init(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void	prompt_init(t_mini *mini, int exit_code)
{
	char		*prompt;

	sig_init();
	while (1)
	{
		sigint_received = 0;
		prompt = readline(give_me_prompt(mini));
		if (sigint_received)
		{
			free (prompt);
			free (mini->prompt_msg);
			continue ;
		}
		if (!prompt)
			continue ;
		if (prompt && prompt[0] == '\0')
		{
			free (mini->prompt_msg);
			free (prompt);
			continue ;
		}
		free(mini->prompt_msg);
		add_history(prompt);
		mini->prompt = prompt;
		mini->exitcode = exit_code;
		parse_init(mini);
		//print_commands(mini);
		exec_init(mini);
		free(prompt);
		prompt = NULL;
		exit_code = mini->exitcode;
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	int		exit_code;

	exit_code = 0;
	mini.env = env;
	prompt_init(&mini, exit_code);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}
