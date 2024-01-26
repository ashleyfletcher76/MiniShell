/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:26:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/18 19:21:59 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_all(t_pipex *pipex)
{
	int		i;

	i = 0;
	piper(pipex);
	pipex->pids = malloc((pipex->nbr_cmd) * sizeof(pid_t));
	if (pipex->pids == NULL)
		return (free_struct(pipex), exit(EXIT_FAILURE));
	while (i < pipex->nbr_cmd)
	{
		forker(pipex, i);
		if (pipex->pids[i] == 0)
		{
			if (i == 0)
				first_son(pipex, i);
			else if (i == pipex->nbr_cmd - 1)
				last_son(pipex, i);
			else
				daughters(pipex, i);
		}
		i++;
	}
}

void	first_son(t_pipex *pipex, int i)
{
	int		fd;
	char	*path;

	fd = opener(pipex, 0);
	dup2er(fd, pipex->pipel[i][WRITE_END], pipex);
	close(fd);
	path = get_a_path(pipex->command_paths[i][0], pipex, i);
	pipe_close(pipex);
	execve(path, pipex->command_paths[i], pipex->env);
}

void	last_son(t_pipex *pipex, int i)
{
	int		fd;
	char	*path;

	fd = opener(pipex, 1);
	dup2er(pipex->pipel[i - 1][READ_END], fd, pipex);
	close(fd);
	path = get_a_path(pipex->command_paths[i][0], pipex, i);
	pipe_close(pipex);
	execve(path, pipex->command_paths[i], pipex->env);
}

void	daughters(t_pipex *pipex, int i)
{
	char	*path;

	dup2(pipex->pipel[i - 1][READ_END], STDIN_FILENO);
	dup2(pipex->pipel[i][WRITE_END], STDOUT_FILENO);
	path = get_a_path(pipex->command_paths[i][0], pipex, i);
	pipe_close(pipex);
	execve(path, pipex->command_paths[i], pipex->env);
}

void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd - 1)
	{
		close(pipex->pipel[i][READ_END]);
		close(pipex->pipel[i][WRITE_END]);
		i++;
	}
}
