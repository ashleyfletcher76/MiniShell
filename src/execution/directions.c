/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/20 13:40:47 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	direction_handler(t_pipex *pipex)
{
	output_handler(pipex);
	input_handler(pipex);
}

void	heredoc_found(t_pipex *pipex)
{
	ft_printf("%s", pipex->commands->input[0]);
}

void	input_handler(t_pipex *pipex)
{
	int	fd;

	fd = 0;
	if (pipex->commands->indicator_input[0] == TRUE)
		return (heredoc_found(pipex));
	if (pipex->commands->input[0] != NULL)
	{
		pipex->fd_in_orj = dup(STDIN_FILENO);
		fd = open(pipex->commands->input[0], O_RDONLY);
		if (fd == -1)
		{
			perror("minishell: input");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			free_struct(pipex);
			exit(9);
		}
		close(fd);
	}
}

void	output_handler(t_pipex *pipex)
{
	int	fd;

	fd = 0;
	if (pipex->commands->output != NULL)
	{
		pipex->fd_out_orj = dup(STDOUT_FILENO);
		if (pipex->commands->indicator_output == FALSE)
			fd = open(pipex->commands->output[0], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(pipex->commands->output[0], O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
		{
			write(2, "minishell: ", 18);
			perror(pipex->commands->output[0]);
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			free_struct(pipex);
			exit(9);
		}
		close(fd);
	}
}
