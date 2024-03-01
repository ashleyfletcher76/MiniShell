/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:07:48 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 13:35:56 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_input_arg(t_commands **cmd, char **temp, int flag)
{
	int	i;

	i = (*cmd)->input_index + (*cmd)->output_index;
	if (!*temp)
		return ;
	(*cmd)->input = ft_realloc_char((*cmd)->input, (*cmd)->input_index);
	(*cmd)->input[(*cmd)->input_index] = ft_strdup(*temp);
	if (!(*cmd)->input[(*cmd)->input_index])
		return ;
	(*cmd)->indicator_input = ft_realloc_int((*cmd)->indicator_input,
			(*cmd)->input_index);
	if (flag)
		(*cmd)->indicator_input[(*cmd)->input_index] = TRUE;
	else
		(*cmd)->indicator_input[(*cmd)->input_index] = FALSE;
	(*cmd)->order_input = ft_realloc_int((*cmd)->order_input, i);
	(*cmd)->order_input[(*cmd)->input_index] = i + 1;
	(*cmd)->input_index++;
	(*cmd)->input[(*cmd)->input_index] = NULL;
}

void	update_output_arg(t_commands **cmd, char **temp, int flag)
{
	int	i;

	i = (*cmd)->input_index + (*cmd)->output_index;
	if (!*temp)
		return ;
	(*cmd)->output = ft_realloc_char((*cmd)->output, (*cmd)->output_index);
	(*cmd)->output[(*cmd)->output_index] = ft_strdup(*temp);
	if (!(*cmd)->output[(*cmd)->output_index])
		return ;
	(*cmd)->indicator_output = ft_realloc_int((*cmd)->indicator_output,
			(*cmd)->output_index);
	if (flag)
		(*cmd)->indicator_output[(*cmd)->output_index] = TRUE;
	else
		(*cmd)->indicator_output[(*cmd)->output_index] = FALSE;
	(*cmd)->order_output = ft_realloc_int((*cmd)->order_output, i);
	(*cmd)->order_output[(*cmd)->output_index] = i + 1;
	(*cmd)->output_index++;
	(*cmd)->output[(*cmd)->output_index] = NULL;
}

char	*append_heredoc(t_mini *mini, char *temp)
{
	char	*new_str;
	char	*original_temp;
	int		first_line;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	original_temp = ft_strdup(temp);
	free (temp);
	if (!original_temp)
	{
		free (new_str);
		return (NULL);
	}
	first_line = 1;
	new_str = full_heredoc(mini, original_temp, new_str, first_line);
	free (original_temp);
	return (new_str);
}

char	*full_heredoc(t_mini *mini, char *orig_str, char *new_str, int first)
{
	char	*read_line;

	while (1)
	{
		read_line = readline("heredoc> ");
		if (!read_line || ft_strcmp(read_line, orig_str) == 0)
		{
			free (read_line);
			break ;
		}
		if (!first)
			new_str = ft_char_join(new_str, '\n');
		else
			first = 0;
		new_str = ft_strjoin_freeself(new_str, read_line);
		new_str = check_expand_heredoc(mini, new_str);
	}
	mini->expand_heredoc = 0;
	return (ft_char_join(new_str, '\n'));
}
