/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:07:48 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/27 12:01:35 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_input_arg(t_commands **cmd, char **temp, int flag)
{
	int	i;

	i = (*cmd)->input_index + (*cmd)->output_index;
	if (!*temp)
		return ;
	(*cmd)->input = ft_realloc_double_char((*cmd)->input, (*cmd)->input_index);
	(*cmd)->input[(*cmd)->input_index] = ft_strdup(*temp);
	if (!(*cmd)->input[(*cmd)->input_index])
			return ;
	(*cmd)->indicator_input = ft_realloc_int((*cmd)->indicator_input, (*cmd)->input_index);
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
	(*cmd)->output = ft_realloc_double_char((*cmd)->output, (*cmd)->output_index);
	(*cmd)->output[(*cmd)->output_index] = ft_strdup(*temp);
	if (!(*cmd)->output[(*cmd)->output_index])
			return ;
	(*cmd)->indicator_output = ft_realloc_int((*cmd)->indicator_output, (*cmd)->output_index);
	if (flag)
		(*cmd)->indicator_output[(*cmd)->output_index] = TRUE;
	else
		(*cmd)->indicator_output[(*cmd)->output_index] = FALSE;
	(*cmd)->order_output = ft_realloc_int((*cmd)->order_output, i);
	(*cmd)->order_output[(*cmd)->output_index] = i + 1;
	(*cmd)->output_index++;
	(*cmd)->output[(*cmd)->output_index] = NULL;
}

char	*append_heredoc(char *temp)
{
	char	*new_str;
	char	*original_temp;
	char	*new_line;
	int		first_line;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	original_temp = ft_strdup(temp);
	if (!original_temp)
	{
		free (new_str);
		return (NULL);
	}
	new_line = "\n";
	first_line = 1;
	new_str = full_heredoc(original_temp, new_str, new_line, first_line);
	free (original_temp);
	return (new_str);
}

char	*full_heredoc(char *orig_str, char *new_str, char *new_line, int first_line)
{
	char	*read_line;
	char	*temp_str;

	while (1)
	{
		read_line = readline("heredoc> ");
		if (!read_line || ft_strcmp(read_line, orig_str) == 0)
		{
			free (read_line);
			break ;
		}
		if (!first_line)
		{
			temp_str = ft_strjoin(new_str, new_line);
			free (new_str);
			new_str = temp_str;
		}
		else
			first_line = 0;
		temp_str = ft_strjoin(new_str, read_line);
		free (new_str);
		new_str = temp_str;
		free (read_line);
	}
	return (ft_char_join(new_str, '\n'));
}
