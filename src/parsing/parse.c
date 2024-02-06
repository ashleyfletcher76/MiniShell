/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/04 12:03:54 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	parse_init(t_mini *mini)
{
	char **argv;

	argv = ft_split(mini->prompt, '|');
	
	
	mini->argv = argv;
	if (is_built_in(mini) == 0)
	{
		pipex_main(argv, mini->env);
	}




}
