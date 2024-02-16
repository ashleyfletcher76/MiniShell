/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:07:48 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/16 17:56:50 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_input_arg(t_commands **cmd, char **temp, int flag)
{
	int	fd;

	if (!*temp)
		return ;
	if (flag)
	{
		if (!(*cmd)->output)
			free ((*cmd)->input);
		(*cmd)->indicator_input = TRUE;
		(*cmd)->input = ft_strdup(*temp);
		if (!(*cmd)->input)
			return ;
	}
	else
	{
		if (!(*cmd)->input)
			free ((*cmd)->input);
		(*cmd)->indicator_input = FALSE;
		(*cmd)->input = ft_strdup(*temp);
		if (!(*cmd)->output)
			return ;
		fd = open((*cmd)->input, O_RDONLY, 0644);
		close(fd);
	}
}

void	update_output_arg(t_commands **cmd, char **temp, int flag)
{
	int	fd;

	if (!*temp)
		return ;
	if (flag)
	{
		if (!(*cmd)->output)
			free ((*cmd)->output);
		(*cmd)->indicator_output = TRUE;
		(*cmd)->output = ft_strdup(*temp);
		if (!(*cmd)->output)
			return ;
		fd = open((*cmd)->output, O_CREAT | O_APPEND, 0644);
		close(fd);
	}
	else
	{
		if (!(*cmd)->output)
			free ((*cmd)->output);
		(*cmd)->indicator_output = FALSE;
		(*cmd)->output = ft_strdup(*temp);
		if (!(*cmd)->output)
			return ;
		fd = open((*cmd)->output, O_CREAT | O_TRUNC, 0644);
		close(fd);
	}
}

//doesnt work with space after hi/ delim
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
		read_line = readline("here_doc> ");
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
	return (new_str);
}
