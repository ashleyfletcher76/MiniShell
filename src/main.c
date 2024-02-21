/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/21 16:03:49 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	promt_init(t_mini *mini)
{
	char		*prompt;
	static int	exitcode;

	while (1)
	{
		prompt = readline(give_me_prompt(mini));
		if (!prompt)
			exit(EXIT_FAILURE);
		free(mini->prompt_msg);
		add_history(prompt);
		mini->prompt = prompt;
		mini->exitcode = exitcode;
		parse_init(mini);
		print_commands(mini);
		exec_init(mini);
		free(prompt);
		prompt = NULL;
		exitcode = mini->exitcode;
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	mini.env = env;
	promt_init(&mini);
	(void)ac;
	(void)av;
	return (EXIT_SUCCESS);
}
