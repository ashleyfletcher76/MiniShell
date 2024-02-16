/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/16 15:59:50 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	promt_init(t_mini *mini)
{
	char	*prompt;

	while (1)
	{
		prompt = readline(give_me_prompt(mini));
		if (!prompt)
			exit(EXIT_FAILURE);
		free(mini->prompt_msg);
		add_history(prompt);
		mini->prompt = prompt;
		parse_init(mini);
		exec_init(mini);
		free(prompt);
		prompt = NULL;
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
