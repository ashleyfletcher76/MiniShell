/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:44:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/13 15:21:50 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_built_in(t_pipex *pipex)
{
	if (pipex->commands->cmd_args[0])
	{	
		if (exist_build(pipex->commands->cmd_args))
		{
			direction_handler(pipex);
			which_build(pipex->commands->cmd_args, pipex->env);
			if (pipex->commands->input != NULL)
				dup2(pipex->fd_in_orj, STDIN_FILENO);
			if (pipex->commands->output != NULL)
				dup2(pipex->fd_out_orj, STDOUT_FILENO);
			return (TRUE);
		}
	}
	return (FALSE);
}


int	which_build(char **commands, char **env)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (ft_cd(commands, env), TRUE);
	if (ft_strncmp(commands[0], "exit", 6) == 0)
		return (ft_exit(commands), TRUE);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		return (ft_export(commands, env), TRUE);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (ft_unset(commands, env), TRUE);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (ft_pwd(), TRUE);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		return (ft_env(env), TRUE);
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		return (ft_echo(commands), TRUE);
	return (FALSE);
}

int	exist_build(char **commands)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "exit", 6) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		return (TRUE);
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		return (TRUE);
	return (FALSE);
}
