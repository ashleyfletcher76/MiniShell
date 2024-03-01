/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:21:29 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 12:10:56 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_helper(t_mini *mini, int *i, char *temp)
{
	while (no_whitespace_skip(mini->prompt[*i]) && mini->prompt[*i] != '|')
	{
		if (mini->prompt[*i] == '\"')
		{
			if (!temp)
				temp = ft_strdup("");
			temp = ft_strjoin_freeself(temp, parse_double_heredoc(mini, i));
			mini->expand_heredoc = 1;
			(*i)++;
		}
		else if (mini->prompt[*i] == '\'')
		{
			if (!temp)
				temp = ft_strdup("");
			temp = ft_strjoin_freeself(temp, parse_single_quote(mini, i));
			mini->expand_heredoc = 1;
			(*i)++;
		}
		if (no_whitespace_skip(mini->prompt[*i]) && mini->prompt[*i] != '\"'
			&& mini->prompt[*i] != '|' && mini->prompt[*i] != '\'')
			temp = ft_char_join(temp, mini->prompt[(*i)++]);
	}
	return (temp);
}

void	parse_input(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;
	int		flag;

	flag = 0;
	temp = NULL;
	(*i)++;
	if (mini->prompt[*i] == '<')
	{
		(*i)++;
		flag = 1;
	}
	while ((iswhitespace(mini->prompt[*i])) && mini->prompt[*i])
		(*i)++;
	temp = (parse_helper(mini, i, temp));
	if (flag)
		temp = append_heredoc(mini, temp);
	if (mini->prompt[*i] == '\0' || mini->prompt[*i] == '|')
		(*i)--;
	update_input_arg(cmd, &temp, flag);
	free (temp);
	temp = NULL;
}

void	parse_output(t_mini *mini, int *i, t_commands **cmd)
{
	char	*temp;
	int		flag;

	flag = 0;
	temp = NULL;
	(*i)++;
	if (mini->prompt[*i] == '>')
	{
		(*i)++;
		flag = 1;
	}
	while ((iswhitespace(mini->prompt[*i])) && mini->prompt[*i] != '\0')
		(*i)++;
	temp = parse_helper(mini, i, temp);
	if (mini->prompt[*i] == '\0' || mini->prompt[*i] == '|')
		(*i)--;
	update_output_arg(cmd, &temp, flag);
	free (temp);
	temp = NULL;
}
