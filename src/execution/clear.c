/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:04:18 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 12:39:15 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_struct(t_mini *mini)
{
	free_double_array(mini->all_paths);
	if (mini->pipel != NULL)
		free_double_int(mini->pipel, mini->nbr_cmd);
	if (mini->pids != NULL)
		free(mini->pids);
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
	g_sigint_received = 0;
}
