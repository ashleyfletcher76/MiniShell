/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/13 17:24:43 by asfletch         ###   ########.fr       */
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
