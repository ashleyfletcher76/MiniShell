/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:56:59 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 14:40:29 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_saver_input(t_mini *mini)
{
	mini->fd_in_orj = dup(STDIN_FILENO);
	if (mini->fd_in_orj == -1)
	{
		perror("dup");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			cleaner(mini);
			prompt_init(mini, 9);
			return ;
		}
		all_cleaner(mini);
		exit(9);
	}
}

void	dup_saver_output(t_mini *mini)
{
	mini->fd_out_orj = dup(STDOUT_FILENO);
	if (mini->fd_out_orj == -1)
	{
		perror("dup");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			cleaner(mini);
			prompt_init(mini, 9);
			return ;
		}
		all_cleaner(mini);
		exit(9);
	}
}

int	input_opener(t_mini *mini, char *s)
{
	int	fd;

	fd = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("minihell: input");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			cleaner(mini);
			prompt_init(mini, 1);
			return (1);
		}
		all_cleaner(mini);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	output_opener(t_mini *mini, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("minishell: output");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			cleaner(mini);
			prompt_init(mini, 1);
			return (1);
		}
		all_cleaner(mini);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	output_append_opener(t_mini *mini, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("minishell: output");
		if ((mini->nbr_cmd == 1 && mini->nbr_cmd_builts == 1)
			|| mini->nbr_cmd == 0)
		{
			if (mini->temp_cmds->input_index != 0)
				input_dup2(mini->fd_in_orj, mini);
			if (mini->temp_cmds->output_index != 0)
				output_dup2(mini->fd_out_orj, mini);
			cleaner(mini);
			prompt_init(mini, 1);
			return (1);
		}
		all_cleaner(mini);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
