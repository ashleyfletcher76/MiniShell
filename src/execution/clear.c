/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:04:18 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 13:08:45 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_pipex *pipex)
{
	free_double_array(pipex->all_paths);
	if (pipex->pipel != NULL)
		free_double_int(pipex->pipel, pipex->nbr_cmd);
	if (pipex->pids != NULL)
		free(pipex->pids);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != 0)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_double_int(int **array, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	waiter(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	while (i < pipex->nbr_cmd)
	{
		waitpid(pipex->pids[i++], &status, 0);
		pipex->exitcode = WEXITSTATUS(status);
	}
	g_sigint_received = 0;
}
