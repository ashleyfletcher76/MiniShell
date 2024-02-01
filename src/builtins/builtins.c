/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:44:12 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/01 14:43:39 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <sys/stat.h>

int	is_built_in(char **commands)
{
	int	i;
	
	i = 0;
	while (commands[i])
	{
		if ((build_get_args(commands[i++])) == 0)
			return (0);
	}
	return (1);
}

int	build_get_args(char *command)
{
	char	*temp;
	char	**cmd_paths;

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
	if (which_build(cmd_paths) == 0)
		return (0);
	return (1);
}

int	which_build(char **commands)
{
	if (ft_strncmp(commands[0], "cd", 3) == 0)
	{
		return (ft_cd(commands) ,1);
	}
	if (ft_strncmp(commands[0], "exit", 5) == 0)
	{
		return (ft_exit(commands) ,1);
	}






	return (0);
}

int	checkPathExistence(const char *path)
{
	struct stat buffer;

	return (stat(path, &buffer) == 0);
}

void	ft_cd(char **command)
{
	char *home;

	home = getenv("HOME");
	if (command[1] == NULL || ft_strncmp(command[1], "~", 2) == 0 )
	{
		chdir(home);
	}
	else if (checkPathExistence(command[1]) || ft_strncmp(command[1], "..", 3) == 0 || ft_strncmp(command[1], ".", 2) == 0)
	{
		chdir(command[1]);
	}
	else
	{
		write(2, "cd: no such file or directory: ", 32);
		ft_putendl_fd(command[1], 2);
	}
}
