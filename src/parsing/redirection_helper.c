/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:07:48 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/13 17:14:37 by asfletch         ###   ########.fr       */
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
		fd = open((*cmd)->output, O_CREAT | O_TRUNC, 0644);
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

// void	append_heredoc(t_commands **cmd, char **temp)
// {
// 	char	*temp1;
// 	//char	*temp2;
// 	char	*new_str;
// 	char	*new_here_doc;

// 	temp2 = ft_strdup("");
// 	new_str = temp;
// 	while (1)
// 	{
// 		temp1 = readline("here_doc> ");
// 		if (!temp1)
// 			break ;
// 		if (ft_strcmp(temp1, new_str) == 0)
// 		{
// 			return (temp1);
// 		}

// 		if ()
// 	}
// }
