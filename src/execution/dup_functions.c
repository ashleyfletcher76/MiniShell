/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:14:47 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/04 10:35:18 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_dup2(int input, t_mini *mini)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			prompt_init(mini, 9);
			return ;
		}
		all_cleaner(mini);
		exit(9);
	}
}

void	output_dup2(int input, t_mini *mini)
{
	if (dup2(input, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		if (mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			prompt_init(mini, 9);
			return ;
		}
		all_cleaner(mini);
		exit(9);
	}
}
