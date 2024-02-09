/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:44:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/09 12:45:20 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_built_in(t_mini *mini)
{
	int	i;
	
	i = 0;
	while (mini->argv[i])
	{
		if ((build_get_args(mini->argv[i], mini->env)) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	build_get_args(char *command, char **env)
{
	char	**cmd_paths;
	char	*temp;

	if (ft_strchr(command, '\''))
	{
		cmd_paths = ft_split(command, '\'');
		temp = ft_strtrim(cmd_paths[0], " \n\t\v");
		free(cmd_paths[0]);
		cmd_paths[0] = temp;
		temp = ft_strtrim(cmd_paths[2], " \n\t\v");
		free(cmd_paths[2]);
		cmd_paths[2] = temp;
	}
	else if (ft_strchr(command, '\"'))
	{
		cmd_paths = ft_split(command, '\"');
		temp = ft_strtrim(cmd_paths[0], " \n\t\v");
		free(cmd_paths[0]);
		cmd_paths[0] = temp;
	}
	else
		cmd_paths = ft_split(command, ' ');
	if (which_build(cmd_paths, env) == 0)
		return (0);
	return (1);
}

int	which_build(char **commands, char **env)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
	{
		return (ft_cd(commands, env) ,1);
	}
	if (ft_strncmp(commands[0], "exit", 5) == 0)
	{
		return (ft_exit(commands) ,1);
	}
	if (ft_strncmp(commands[0], "export", 6) == 0)
	{
		return (ft_export(commands, env) ,1);
	}
	if (ft_strncmp(commands[0], "unset", 5) == 0)
	{
		return (ft_unset(commands, env) ,1);
	}

	return (0);
}
