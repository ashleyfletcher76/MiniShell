/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/11 10:52:33 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*prompt;
	t_mini	mini;

	mini.env = env;
	while (1)
	{
		prompt = readline(give_me_prompt(&mini));
		if (!prompt)
			exit(EXIT_FAILURE);
		free(mini.prompt_msg);
		add_history(prompt);
		mini.prompt = prompt;
		parse_init(&mini);
		exec_init(&mini);
		free(prompt);
	}
	(void)ac;
	(void)av;
	rl_clear_history();
	return (EXIT_SUCCESS);
}
