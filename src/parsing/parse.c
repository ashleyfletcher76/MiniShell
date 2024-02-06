/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/06 14:28:00 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_trial(t_mini *mini)
{
	mini->commands.args = ft_split(mini->prompt, '|');
	if (!mini->commands.args)
		return ;
	
}


void	parse_init(t_mini *mini)
{
	char **argv;

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');


	mini->argv = argv;
	if (is_built_in(mini) == 0)
	{
		pipex_main(argv, mini->env);
	}




}
