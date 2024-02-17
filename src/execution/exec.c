/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/17 10:32:59 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_init(t_mini *mini)
{
	exec_main(mini);
}

void	exec_main(t_mini *mini)
{
	t_pipex	pipex;

	pipex.nbr_cmd = commands_size_all(mini->commands);
	pipex.env = mini->env;
	pipex.commands = mini->commands;
	pipex.exitcode = mini->exitcode;
	pipex.nbr_cmd_builts = commands_size_buildin(mini->commands);
	if (pipex.nbr_cmd_builts == 1 && pipex.nbr_cmd == 1)
	{
		is_built_in(&pipex);
		if (pipex.commands->input != NULL)
			dup2(pipex.fd_in_orj, STDIN_FILENO);
		if (pipex.commands->output != NULL)
			dup2(pipex.fd_out_orj, STDOUT_FILENO);
		return ;
	}
	get_adresses(&pipex);
	pipe_all(&pipex);
	pipe_close(&pipex);
	waiter(&pipex);
	mini->exitcode = pipex.exitcode;
	//free_struct(&pipex);
}
