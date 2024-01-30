/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/01/30 14:16:27 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	parse_init(t_mini *mini)
{
	char **argv;
	int	i = 0;
	int j = 0;
	argv = ft_split(mini->prompt, '|');

	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] == '\'')
				printf("asdasd\n");
			j++;
		}
		
		i++;
	}
	pipex_main(argv, mini->env);




}
