/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:21:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/20 13:45:35 by asfletch         ###   ########.fr       */
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
	while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '|')
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	if (flag)
		temp = append_heredoc(temp);
	if (mini->prompt[*i] == '\0' || mini->prompt[*i] == '|')
		(*i)--;
	update_input_arg(cmd, &temp, flag);
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
	while ((mini->prompt[*i] == ' ' || mini->prompt[*i] == '\t') && mini->prompt[*i + 1] != '\0')
		(*i)++;
	while (mini->prompt[*i] != ' ' && mini->prompt[*i])
	{
		temp = ft_char_join(temp, mini->prompt[*i]);
		(*i)++;
	}
	if (mini->prompt[*i] == '\0')
		(*i)--;
	update_output_arg(cmd, &temp, flag);
	free (temp);
	temp = NULL;
}
