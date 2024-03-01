/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:26:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 13:24:53 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_all(t_mini *mini)
{
	int			i;

	i = 0;
	piper(mini);
	mini->pids = malloc((mini->nbr_cmd) * sizeof(pid_t));
	if (mini->pids == NULL)
		return (all_cleaner(mini), exit(EXIT_FAILURE));
	g_sigint_received = 1;
	while (i < mini->nbr_cmd)
	{
		forker(mini, i);
		if (mini->pids[i] == 0)
		{
			if (i == 0 && mini->nbr_cmd == 1)
				only_child(mini, i);
			else if (i == 0 && mini->nbr_cmd != 1)
				first_son(mini, i);
			else if (i == mini->nbr_cmd - 1)
				last_son(mini, i);
			else
				daughters(mini, i);
		}
		i++;
		mini->temp_cmds = mini->temp_cmds->next;
	}
}

void	only_child(t_mini *mini, int i)
{
	char	*path;

	(void)i;
	pipe_close(mini);
	direction_handler(mini);
	if (is_built_in(mini))
	{
		all_cleaner(mini);
		exit(EXIT_SUCCESS);
	}
	path = get_a_path(mini->temp_cmds->cmd_args[0], mini);
	execve(path, mini->temp_cmds->cmd_args, mini->env);
}

void	first_son(t_mini *mini, int i)
{
	char	*path;

	direction_handler(mini);
	if (mini->temp_cmds->output_index == 0)
		dup2(mini->pipel[i][WRITE_END], STDOUT_FILENO);
	pipe_close(mini);
	if (is_built_in(mini))
	{
		all_cleaner(mini);
		exit(EXIT_SUCCESS);
	}
	path = get_a_path(mini->temp_cmds->cmd_args[0], mini);
	execve(path, mini->temp_cmds->cmd_args, mini->env);
}

void	last_son(t_mini *mini, int i)
{
	char	*path;

	direction_handler(mini);
	if (mini->temp_cmds->input_index == 0)
		dup2(mini->pipel[i - 1][READ_END], STDIN_FILENO);
	pipe_close(mini);
	if (is_built_in(mini))
	{
		all_cleaner(mini);
		exit(EXIT_SUCCESS);
	}
	path = get_a_path(mini->temp_cmds->cmd_args[0], mini);
	execve(path, mini->temp_cmds->cmd_args, mini->env);
}

void	daughters(t_mini *mini, int i)
{
	char	*path;

	direction_handler(mini);
	if (mini->temp_cmds->input_index == 0)
		dup2(mini->pipel[i - 1][READ_END], STDIN_FILENO);
	if (mini->temp_cmds->output_index == 0)
		dup2(mini->pipel[i][WRITE_END], STDOUT_FILENO);
	pipe_close(mini);
	if (is_built_in(mini))
	{
		all_cleaner(mini);
		exit(EXIT_SUCCESS);
	}
	path = get_a_path(mini->temp_cmds->cmd_args[0], mini);
	execve(path, mini->temp_cmds->cmd_args, mini->env);
}
