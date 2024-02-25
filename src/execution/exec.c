/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/25 09:55:22 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_mini *mini)
{
	exec_main(mini);
}

void	init_built_in(t_pipex *pipex, t_mini *mini)
{
	if (pipex->commands->input_index != 0)
		dup_saver(pipex, STDIN_FILENO);
	if (pipex->commands->output_index != 0)
		dup_saver(pipex, STDOUT_FILENO);
	is_built_in(pipex);
	if (pipex->commands->input_index != 0)
		input_dup2(pipex->fd_in_orj, pipex);
	if (pipex->commands->output_index != 0)
		output_dup2(pipex->fd_out_orj, pipex);
	mini->exitcode = pipex->exitcode;
	//clean 
	return ;
}

void	exec_main(t_mini *mini)
{
	t_pipex	pipex;

	pipex.nbr_cmd = commands_size_all(mini->commands);
	pipex.env = mini->env;
	pipex.commands = mini->commands;
	pipex.exitcode = mini->exitcode;
	pipex.mini = mini;
	pipex.nbr_cmd_builts = commands_size_buildin(mini->commands);
	if (pipex.nbr_cmd_builts == 1 && pipex.nbr_cmd == 1)
		return (init_built_in(&pipex, mini));
	get_adresses(&pipex);
	pipe_all(&pipex);
	pipe_close(&pipex);
	waiter(&pipex);
	mini->exitcode = pipex.exitcode;
}
