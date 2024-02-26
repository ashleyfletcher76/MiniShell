/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:30:42 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/26 18:03:19 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_mini *mini)
{
	int	i;

	i = 0;
	while ((mini->prompt[i] == '\t' || mini->prompt[i] == ' ') && mini->prompt[i] != '\0')
		i++;
	if (mini->prompt[i] == '|')
		return (ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2), FALSE);
	while (mini->prompt[i])
	{
		if (mini->prompt[i] == '|')
		{
			i++;
			while ((mini->prompt[i] == '\t' || mini->prompt[i] == ' ') && (mini->prompt[i] != '\0' || mini->prompt[i] != '|'))
				i++;
			if (mini->prompt[i] == '|')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2), FALSE);
		}
		i++;
	}
	return (TRUE);
}






/*
			if (mini->prompt[i] == '\0')
				{
					while (1)
					{
						int j = 0;
						temp = readline("pipe>");
						mini->prompt = ft_strjoin_freeself(mini->prompt, temp);
						while ((temp[j] == '\t' || temp[j] == ' ') && temp[j] != '\0')
							j++;
						if (temp[j] != '\0')
							break ;
					}
				}//mini->prompt = 
			while ((mini->prompt[i] == '\t' || mini->prompt[i] == ' ') && (mini->prompt[i] != '\0' || mini->prompt[i] != '|'))
				i++;
			if (mini->prompt[i] == '|')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2), FALSE);*/
