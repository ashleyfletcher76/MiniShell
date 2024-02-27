/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:26:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 10:21:42 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "structs.h"

void	pipe_all(t_pipex *pipex)
{
	int			i;

	i = 0;
	piper(pipex);
	pipex->pids = malloc((pipex->nbr_cmd) * sizeof(pid_t));
	if (pipex->pids == NULL)
		return (free_struct(pipex), exit(EXIT_FAILURE));
	sigint_received = 1;
	while (i < pipex->nbr_cmd)
	{
		forker(pipex, i);
		if (pipex->pids[i] == 0)
		{
			if (i == 0 && pipex->nbr_cmd == 1)
				only_child(pipex, i);
			else if (i == 0 && pipex->nbr_cmd != 1)
				first_son(pipex, i);
			else if (i == pipex->nbr_cmd - 1)
				last_son(pipex, i);
			else
				daughters(pipex, i);
		}
		i++;
		pipex->commands = pipex->commands->next;
	}
}

void	only_child(t_pipex *pipex, int i)
{
	char	*path;

	(void)i;
	pipe_close(pipex);
	direction_handler(pipex);
	if (is_built_in(pipex))
		exit(EXIT_SUCCESS);
	path = get_a_path(pipex->commands->cmd_args[0], pipex);
	execve(path, pipex->commands->cmd_args, pipex->env);
	exit(EXIT_SUCCESS);
}

void	first_son(t_pipex *pipex, int i)
{
	char	*path;

	direction_handler(pipex);
	if (pipex->commands->output_index == 0)
		dup2(pipex->pipel[i][WRITE_END], STDOUT_FILENO);
	pipe_close(pipex);
	if (is_built_in(pipex))
		exit(EXIT_SUCCESS);
	path = get_a_path(pipex->commands->cmd_args[0], pipex);
	execve(path, pipex->commands->cmd_args, pipex->env);
}

void	last_son(t_pipex *pipex, int i)
{
	char	*path;

	direction_handler(pipex);
	if (pipex->commands->input_index == 0)
		dup2(pipex->pipel[i - 1][READ_END], STDIN_FILENO);
	pipe_close(pipex);
	if (is_built_in(pipex))
		exit(EXIT_SUCCESS);
	path = get_a_path(pipex->commands->cmd_args[0], pipex);
	execve(path, pipex->commands->cmd_args, pipex->env);
}

void	daughters(t_pipex *pipex, int i)
{
	char	*path;

	direction_handler(pipex);
	if (pipex->commands->input_index == 0)
		dup2(pipex->pipel[i - 1][READ_END], STDIN_FILENO);
	if (pipex->commands->output_index == 0)
		dup2(pipex->pipel[i][WRITE_END], STDOUT_FILENO);
	pipe_close(pipex);
	if (is_built_in(pipex))
		exit(EXIT_SUCCESS);
	path = get_a_path(pipex->commands->cmd_args[0], pipex);
	execve(path, pipex->commands->cmd_args, pipex->env);
}

void	pipe_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbr_cmd - 1)
	{
		close(pipex->pipel[i][READ_END]);
		close(pipex->pipel[i][WRITE_END]);
		i++;
	}
}
