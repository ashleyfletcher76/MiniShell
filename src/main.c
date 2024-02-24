/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/24 14:44:42 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	prompt_init(t_mini *mini, int exit_code)
{
	char		*prompt;

	while (1)
	{
		prompt = readline(give_me_prompt(mini));
		if (!prompt)
			exit(EXIT_FAILURE);
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
