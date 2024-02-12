/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:21:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/12 09:21:48 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_input(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	while (mini->prompt[*i] != ' ' && mini->prompt[*i])
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	(*cmd)->input = ft_strdup(temp);
	free (temp);
	while (mini->prompt[*i] == ' ' && mini->prompt[*i])
		(*i)++;
}

void	parse_output(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;

	temp = NULL;
	(*i)++;
	while (mini->prompt[*i] != ' ' && mini->prompt[*i])
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	(*cmd)->output = temp;
	free (temp);
	while (mini->prompt[*i] == ' ' && mini->prompt[*i + 1] == ' ')
		(*i)++;
}
