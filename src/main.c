/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/04 07:44:03 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_flag = 0;

void	prompt_init(t_mini *mini, int exit_code)
{
	char		*prompt;

	while (1)
	{
		g_signal_flag = 0;
		prompt = readline("Minishell$ ");
		if (!prompt)
		{
			printf("exit\n");
			rl_clear_history();
			free_double_array(mini->env);
			free_double_array(mini->export);
			exit(EXIT_SUCCESS);
		}
		add_history(prompt);
		mini->prompt = prompt;
		mini->exitcode = exit_code;
		parse_init(mini);
		prompt = NULL;
		exit_code = mini->exitcode;
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	int		exit_code;

	sig_init();
	configure_terminal();
	exit_code = 0;
	struct_init(&mini, env);
	prompt_init(&mini, exit_code);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}

void	struct_init(t_mini *mini, char **env)
{
	mini->prompt_msg = NULL;
	mini->prompt = NULL;
	mini->env = dup_env(env);
	mini->export = dup_export(env);
	mini->all_paths = NULL;
	mini->exitcode = 0;
	mini->fd_in_orj = 0;
	mini->fd_out_orj = 0;
	mini->nbr_cmd_builts = 0;
	mini->pipel = 0;
	mini->nbr_cmd = 0;
	mini->expand_heredoc = 0;
	mini->pids = NULL;
	mini->commands = NULL;
}
