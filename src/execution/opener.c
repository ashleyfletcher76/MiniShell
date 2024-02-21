/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:56:59 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/20 17:48:29 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	dup_maker(t_pipex *pipex, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 0)
	{
		pipex->fd_in_orj = dup(STDIN_FILENO);
		if (fd == -1)
		{
			perror("dup");
			free_struct(pipex);
			exit(9);
		}
	}
	else
	{
		pipex->fd_in_orj = dup(STDOUT_FILENO);
		if (fd == -1)
		{
			perror("dup");
			free_struct(pipex);
			exit(9);
		}
	}
	return (fd);
}

int	input_opener(t_pipex *pipex, char *s)
{
	int	fd;

	fd = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("minihell: input");
		free_struct(pipex);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	output_opener(t_pipex *pipex, char *s, int flag)
{
	int	fd;

	if (flag == 0)
	{
		fd = open(s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("minishell: output");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
	else
	{
		fd = open(s, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("minishell: output");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
}

void	dup2er(int input, int output, t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
		exit(9);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
		exit(9);
	}
}

void	input_dup2(int input,t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
		exit(9);
	}
}

void	output_dup2(int input,t_pipex *pipex)
{
	if (dup2(input, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
		exit(9);
	}
}
