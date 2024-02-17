/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:07:48 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/17 10:40:27 by asfletch         ###   ########.fr       */
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

// void	*append_heredoc(char *temp)
// {
// 	char	*read_line;
// 	char	*new_str;
// 	char	*original_temp;
// 	char	*read_line_temp;

// 	new_str = ft_strdup("");
// 	if (!new_str)
// 		return (NULL);
// 	original_temp = ft_strdup(temp);
// 	if (!original_temp)
// 	{
// 		free (new_str);
// 		return (NULL);
// 	}
// 	read_line = NULL;
// 	read_line_temp = NULL;
// 	new_str = full_heredoc(original_temp, read_line, new_str, read_line_temp);
// 	free (original_temp);
// 	return (new_str);
// }

// void	*full_heredoc(char *orig_str, char *read_line, char *new_str, char *read_temp)
// {
// 	int		len;
// 	char	*temp_str;

// 	while (1)
// 	{
// 		read_line = readline("here_doc> ");
// 		if (!read_line)
// 			break ;
// 		len = ft_strlen(read_line);
// 		read_temp = malloc(sizeof(read_line) + 2);
// 		if (!read_temp)
// 		{
// 			free (read_line);
// 			break ;
// 		}
// 		ft_memcpy(read_temp, read_line, len);
// 		read_temp[len] = '\n';
// 		read_temp[len + 1] = '\0';
// 		free (read_line);
// 		if ((ft_strcmp(read_line, orig_str)) == 0)
// 		{
// 			len = ft_strlen(new_str);
// 			new_str[len -1] = '\0';
// 			free (read_temp);
// 			break ;
// 		}
// 		temp_str = ft_strjoin(new_str, read_temp);
// 		free (new_str);
// 		new_str = temp_str;
// 	}
// 	return (new_str);
// }


// void	*append_heredoc(char *temp)
// {
// 	char	*temp1;
// 	char	*new_str;
// 	char	*new_here_doc;
// 	char	*original_temp;
// 	int		len;

// 	new_str = ft_strdup("");
// 	original_temp = ft_strdup(temp);
// 	while (1)
// 	{
// 		temp1 = readline("here_doc> ");
// 		if (!temp1)
// 			break ;
// 		if ((ft_strcmp(temp1, original_temp)) == 0)
// 		{
// 			len = ft_strlen(new_str);
// 			new_str[len - 1] = '\0';
// 			free (temp1);
// 			break ;
// 		}
// 		len = ft_strlen(temp1);
// 		temp1[len] = '\n';
// 		temp1[len + 1] = '\0';
// 		new_here_doc = ft_strjoin(new_str, temp1);
// 		free (new_str);
// 		new_str = new_here_doc;
// 	}
// 	return (new_str);
// }
