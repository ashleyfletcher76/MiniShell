/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/04 10:26:55 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_init(t_mini *mini)
{
	exec_main(mini);
}

void	init_built_in(t_mini *mini)
{
	is_built_in(mini);
	if (mini->temp_cmds->input_index != 0)
		input_dup2(mini->fd_in_orj, mini);
	if (mini->temp_cmds->output_index != 0)
		output_dup2(mini->fd_out_orj, mini);
	cleaner(mini);
	return ;
}

void	exec_main(t_mini *mini)
{
	get_adresses(mini);
	mini->temp_cmds = mini->commands;
	mini->nbr_cmd = commands_size_all(mini->commands);
	mini->nbr_cmd_builts = commands_size_buildin(mini->commands);
	if (mini->nbr_cmd_builts == 1 && mini->nbr_cmd == 1)
		return (init_built_in(mini));
	else if (mini->nbr_cmd == 0)
		direction_handler(mini);
	if (mini->nbr_cmd != 0)
	{
		pipe_all(mini);
		pipe_close(mini);
		waiter(mini);
	}
	cleaner(mini);
}
