/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:14:47 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/27 14:31:38 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2er_input(int input, int output, t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
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
	dup2er_output(output, pipex);
}

void	dup2er_output(int output, t_pipex *pipex)
{
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
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

void	input_dup2(int input, t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
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

void	output_dup2(int input, t_pipex *pipex)
{
	if (dup2(input, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		free_struct(pipex);
		if (pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
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
