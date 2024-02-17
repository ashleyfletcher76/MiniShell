/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/16 18:31:59 by muhakose         ###   ########.fr       */
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
	ft_printf("%s", pipex->commands->input);
}

void	input_handler(t_pipex *pipex)
{
	int	fd;

	fd = 0;
	if (pipex->commands->indicator_input == TRUE)
		return (heredoc_found(pipex));
	if (pipex->commands->input != NULL)
	{
		pipex->fd_in_orj = dup(STDIN_FILENO);
		fd = open(pipex->commands->input, O_RDONLY);
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
			fd = open(pipex->commands->output, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else
			fd = open(pipex->commands->output, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("minishell: output");
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
