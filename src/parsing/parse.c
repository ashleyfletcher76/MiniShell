/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/07 10:59:53 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_trial(t_mini *mini)
{
	int	i;
	char *promt;

	promt = mini->prompt;

	// argv = ft_split(mini->prompt, '|');
	i = 0;
	while (promt[i])
	{
		if (promt[i] == '\"')
		{
			i++;
			while (promt[i] != '\"' && promt[i])
			{
				ft_strcpy()
				i++;
			}
			if (promt[i] == '\0')
			{
				printf("flag\n");
				while (1)
				{
					char *temp = readline("dquote> ");
					//append promt with

					if (ft_strchr(temp, '\"'))
						break ;
					free(temp);
				}
			}
			// ft_strcoopy..
		}
		if (promt[i] == '\'')
		{
			i++;
			while (promt[i] != '\'')
			{
				//
				i++;
			}
			if (promt[i] == '\0')
				while (1)
				{
					char *temp = readline("dquote> ");
					//append promt with

					if (ft_strchr(temp, '\''))
						break ;
					free(temp);
				}
			// ft_strcoopy..
		}
		if (promt[i] == '|')
		{
			// head= head->next;
			// ft_strcoopy..
		}


		//addig to node

		i++;
	}

}


void	parse_init(t_mini *mini)
{
	char **argv;

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');

<<<<<<< HEAD

	mini->argv = argv;
	if (is_built_in(mini) == 0)
	{
		pipex_main(argv, mini->env);
	}
=======
	parse_trial(mini);
	// mini->argv = argv;
	// if (is_built_in(mini) == 0)
	// {
	// 	pipex_main(argv, mini->env);
	// }

>>>>>>> ash




}
