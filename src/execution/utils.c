/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 10:23:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 13:27:44 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *msg, t_mini *mini, int exitcode)
{
	ft_put3endl_fd("minishell: ", mini->temp_cmds->cmd_args[0], msg, 2);
	cleaner(mini);
	free_double_array(mini->env);
	rl_clear_history();
	exit (exitcode);
}

void	piper(t_mini *mini)
{
	int	i;

	mini->pipel = (int **)malloc ((mini->nbr_cmd + 1) * sizeof(int *));
	if (mini->pipel == NULL)
		return (free_struct(mini), exit(EXIT_FAILURE));
	i = 0;
	while (i < mini->nbr_cmd - 1)
	{
		mini->pipel[i] = malloc(2 * sizeof(int));
		if (mini->pipel[i] == NULL)
			return (cleaner(mini), exit(EXIT_FAILURE));
		if (pipe(mini->pipel[i]) == -1)
		{
			perror("pipe");
			free_struct(mini);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	mini->pipel[i] = NULL;
}

void	forker(t_mini *mini, int i)
{
	mini->pids[i] = fork();
	if (mini->pids[i] == -1)
	{
		perror("fork");
		free_struct(mini);
		exit(EXIT_FAILURE);
	}
}

void	pipe_close(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->nbr_cmd - 1)
	{
		close(mini->pipel[i][READ_END]);
		close(mini->pipel[i][WRITE_END]);
		i++;
	}
}
