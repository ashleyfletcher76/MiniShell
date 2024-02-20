/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:23:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/20 16:02:57 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/structs.h"

void	error_handler(char *msg, t_pipex *pipex, int exitcode)
{
	ft_put3endl_fd("minishell: ", pipex->commands->cmd_args[0], msg, 2);
	free_struct(pipex);
	exit (exitcode);
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
