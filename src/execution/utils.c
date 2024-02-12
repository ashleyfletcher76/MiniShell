/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:23:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/12 11:10:28 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/pipex.h"

void	error_handler(char *msg, t_pipex *pipex, int exitcode)
{
	ft_put3endl_fd("minishell: ", msg, pipex->commands->cmd_args[0], 2);
	free_struct(pipex);
	exit (exitcode);
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

int	opener(t_pipex *pipex, int m)
{
	int	fd;

	if (m == 0)
	{
		fd = open(pipex->commands->input, O_RDONLY);
		if (fd < 0)
		{
			perror("pipex: input");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
	else
	{
		fd = open(pipex->commands->output, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("pipex: output");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		return (fd);
	}
}

void	piper(t_pipex *pipex)
{
	int	i;

	pipex->pipel = (int **)malloc ((pipex->nbr_cmd) * sizeof(int *));
	if (pipex->pipel == NULL)
		return (free_struct(pipex), exit(EXIT_FAILURE));
	i = 0;
	while (i < pipex->nbr_cmd - 1)
	{
		pipex->pipel[i] = malloc(2 * sizeof(int));
		if (pipex->pipel[i] == NULL)
			return (free_struct(pipex), exit(EXIT_FAILURE));
		if (pipe(pipex->pipel[i]) == -1)
		{
			perror("pipe");
			free_struct(pipex);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	pipex->pipel[i] = NULL;
}

void	forker(t_pipex *pipex, int i)
{
	pipex->pids[i] = fork();
	if (pipex->pids[i] == -1)
	{
		perror("fork");
		free_struct(pipex);
		exit(EXIT_FAILURE);
	}
}
