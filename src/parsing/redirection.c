/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:21:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/12 13:52:37 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_input(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;
	int		flag = 0;

	temp = NULL;
	(*i)++;
	if (mini->prompt[*i] == '<')
	{
		(*i)++;
		flag = 1;
	}
	while ((mini->prompt[*i] == ' ' || mini->prompt[*i] == '\t') && mini->prompt[*i])
		(*i)++;
	while (mini->prompt[*i] != ' ' && mini->prompt[*i])
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	if (flag)
		(*cmd)->double_input = ft_strdup(temp);
	else
		(*cmd)->input = ft_strdup(temp);
	free (temp);
	temp = NULL;
}

void	parse_output(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;
	int		flag = 0;

	temp = NULL;
	(*i)++;
	if (mini->prompt[*i] == '>')
	{
		(*i)++;
		flag = 1;
	}
	while ((mini->prompt[*i] == ' ' || mini->prompt[*i] == '\t') && mini->prompt[*i])
		(*i)++;
	while (mini->prompt[*i] != ' ' && mini->prompt[*i])
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	if (flag)
		(*cmd)->double_output = ft_strdup(temp);
	else
		(*cmd)->output = ft_strdup(temp);
	free (temp);
	temp = NULL;
}
