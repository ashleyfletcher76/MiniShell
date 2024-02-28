/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:56:59 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 13:52:39 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_saver_input(t_pipex *pipex)
{
	pipex->fd_in_orj = dup(STDIN_FILENO);
	if (pipex->fd_in_orj == -1)
	{
		perror("dup");
		cleaner(pipex);
		if ((pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			|| pipex->nbr_cmd == 0)
		{
			if (pipex->commands->input_index != 0)
				input_dup2(pipex->fd_in_orj, pipex);
			if (pipex->commands->output_index != 0)
				output_dup2(pipex->fd_out_orj, pipex);
			prompt_init(pipex->mini, 9);
			return ;
		}
		exit(9);
	}
}

void	dup_saver_output(t_pipex *pipex)
{
	pipex->fd_out_orj = dup(STDOUT_FILENO);
	if (pipex->fd_out_orj == -1)
	{
		perror("dup");
		cleaner(pipex);
		if ((pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			|| pipex->nbr_cmd == 0)
		{
			if (pipex->commands->input_index != 0)
				input_dup2(pipex->fd_in_orj, pipex);
			if (pipex->commands->output_index != 0)
				output_dup2(pipex->fd_out_orj, pipex);
			prompt_init(pipex->mini, 9);
			return ;
		}
		exit(9);
	}
}

int	input_opener(t_pipex *pipex, char *s)
{
	int	fd;

	fd = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("minihell: input");
		cleaner(pipex);
		if ((pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			|| pipex->nbr_cmd == 0)
		{
			if (pipex->commands->input_index != 0)
				input_dup2(pipex->fd_in_orj, pipex);
			if (pipex->commands->output_index != 0)
				output_dup2(pipex->fd_out_orj, pipex);
			prompt_init(pipex->mini, 1);
			return (1);
		}
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	output_opener(t_pipex *pipex, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("minishell: output");
		cleaner(pipex);
		if ((pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			|| pipex->nbr_cmd == 0)
		{
			if (pipex->commands->input_index != 0)
				input_dup2(pipex->fd_in_orj, pipex);
			if (pipex->commands->output_index != 0)
				output_dup2(pipex->fd_out_orj, pipex);
			prompt_init(pipex->mini, 1);
			return (1);
		}
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	output_append_opener(t_pipex *pipex, char *s)
{
	int	fd;

	fd = open(s, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror("minishell: output");
		cleaner(pipex);
		if ((pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			|| pipex->nbr_cmd == 0)
		{
			if (pipex->commands->input_index != 0)
				input_dup2(pipex->fd_in_orj, pipex);
			if (pipex->commands->output_index != 0)
				output_dup2(pipex->fd_out_orj, pipex);
			prompt_init(pipex->mini, 1);
			return (1);
		}
		exit(EXIT_FAILURE);
	}
	return (fd);
}
