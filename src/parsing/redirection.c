/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:21:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/13 12:13:16 by asfletch         ###   ########.fr       */
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
	{
		if (!(*cmd)->input)
			free ((*cmd)->input);
		(*cmd)->input = ft_strdup(temp);
		(*cmd)->indicator_input = TRUE;
	}
	else
	{
		if ((*cmd)->input)
			free ((*cmd)->input);
		(*cmd)->input = ft_strdup(temp);
		(*cmd)->indicator_input = FALSE;
	}
	free (temp);
	temp = NULL;
}

void	parse_output(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;
	int		fd;
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
	{
		(*cmd)->indicator_output = TRUE;
		(*cmd)->output = ft_strdup(temp);
	}
	else
	{
		if (!(*cmd)->output)
			free ((*cmd)->output);
		(*cmd)->indicator_output = FALSE;
		(*cmd)->output = ft_strdup(temp);
		fd = open((*cmd)->output, O_CREAT | O_TRUNC | O_RDONLY, 0644);
		close(fd);
	}
	free (temp);
	temp = NULL;
}
