/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opener.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 15:56:59 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/21 16:56:33 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dup_saver(t_pipex *pipex, int flag)
{
	if (flag == 0)
	{
		pipex->fd_in_orj = dup(STDIN_FILENO);
		if (pipex->fd_in_orj == -1)
		{
			perror("dup");
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
	else
	{
		pipex->fd_out_orj = dup(STDOUT_FILENO);
		if (pipex->fd_out_orj == -1)
		{
			perror("dup");
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
}

int	input_opener(t_pipex *pipex, char *s)
{
	int	fd;

	fd = 0;
	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		perror("minihell: input");
		free_struct(pipex);
		if (pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
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

int	output_opener(t_pipex *pipex, char *s, int flag)
{
	int	fd;

	if (flag == 0)
	{
		fd = open(s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("minishell: output");
			free_struct(pipex);
			if (pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
			{
				if (pipex->commands->input_index != 0)
					input_dup2(pipex->fd_in_orj, pipex);
				if (pipex->commands->output_index != 0)
					output_dup2(pipex->fd_out_orj, pipex);
				prompt_init(pipex->mini, 1);
				return (1);
			}
		}
		return (fd);
	}
	else
	{
		fd = open(s, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd < 0)
		{
			perror("minishell: output");
			free_struct(pipex);
			if (pipex->nbr_cmd == 1 && pipex->nbr_cmd_builts == 1)
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
}

void	dup2er(int input, int output, t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
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
	if (dup2(output, STDOUT_FILENO) == -1)
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

void	input_dup2(int input,t_pipex *pipex)
{
	if (dup2(input, STDIN_FILENO) == -1)
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

void	output_dup2(int input,t_pipex *pipex)
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
