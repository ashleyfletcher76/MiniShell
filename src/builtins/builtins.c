/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:44:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 12:34:18 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_mini *mini)
{
	if (mini->temp_cmds->cmd_args[0])
	{
		if (exist_build(mini->temp_cmds->cmd_args))
		{
			direction_handler(mini);
			which_build(mini->temp_cmds->cmd_args, mini->env, mini);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	which_build(char **commands, char **env, t_mini *mini)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
		return (ft_cd(commands, env, mini), TRUE);
	if (ft_strncmp(commands[0], "exit", 6) == 0)
		return (ft_exit(commands, mini), TRUE);
	if (ft_strncmp(commands[0], "export", 7) == 0)
		return (ft_export(commands, mini), TRUE);
	if (ft_strncmp(commands[0], "unset", 6) == 0)
		return (ft_unset(commands, env, mini), TRUE);
	if (ft_strncmp(commands[0], "pwd", 4) == 0)
		return (ft_pwd(mini), TRUE);
	if (ft_strncmp(commands[0], "env", 4) == 0)
		return (ft_env(env, mini), TRUE);
	if (ft_strncmp(commands[0], "echo", 5) == 0)
		return (ft_echo(commands, mini), TRUE);
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
