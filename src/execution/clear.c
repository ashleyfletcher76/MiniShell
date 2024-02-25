/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:04:18 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/25 09:55:17 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_pipex *pipex)
{
	//free_double_array(pipex->all_paths);
	//free_double_array(pipex->commands->cmd_args);
	//free_double_int(pipex->pipel);
	//free(pipex->pids);
	(void)pipex;
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_tripple_array(char ***array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
	{
		free_double_array(array[i]);
		i++;
	}
	free(array);
}

void	free_double_int(int **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
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
}
