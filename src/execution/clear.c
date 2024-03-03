/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:04:18 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/03 08:54:49 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_mini *mini)
{
	free_double_array(mini->all_paths);
	if (!((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0))
	{
		if (mini->pipel != NULL)
			free_double_int(mini->pipel, mini->nbr_cmd);
		if (mini->pids != NULL)
			free(mini->pids);
	}
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != 0)
		{
			if (array[i] != NULL)
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

void	waiter(t_mini *mini)
{
	int	i;
	int	status;

	i = 0;
	while (i < mini->nbr_cmd)
	{
		waitpid(mini->pids[i++], &status, 0);
		mini->exitcode = WEXITSTATUS(status);
	}
	g_signal_flag = 0;
}
