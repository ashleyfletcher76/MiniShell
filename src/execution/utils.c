/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:23:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 10:38:38 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *msg, t_pipex *pipex, int exitcode)
{
	ft_put3endl_fd("minishell: ", pipex->commands->cmd_args[0], msg, 2);
	free_struct(pipex);
	exit (exitcode);
}

void	piper(t_pipex *pipex)
{
	int	i;

	pipex->pipel = (int **)malloc ((pipex->nbr_cmd + 1) * sizeof(int *));
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
