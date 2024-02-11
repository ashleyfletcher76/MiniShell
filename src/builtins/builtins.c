/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:44:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/11 14:33:46 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_built_in(t_mini *mini)
{
	if (mini->commands[0].cmd_args[0])
	{
		if ((which_build(mini->commands[0].cmd_args, mini->env)) == 0)
			return (0);
	}

	return (1);
}


int	which_build(char **commands, char **env)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (ft_cd(commands, env) ,1);
	if (ft_strncmp(commands[0], "exit", 6) == 0)
		return (ft_exit(commands) ,1);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		return (ft_export(commands, env) ,1);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (ft_unset(commands, env) ,1);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (ft_pwd() ,1);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		return (ft_env(env) ,1);
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		return (ft_echo(commands) ,1);
	return (0);
}
