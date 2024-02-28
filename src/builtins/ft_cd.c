/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:44:16 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 10:22:27 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **command, char **env, t_pipex *pipex)
{
	char	*home;

	pipex->exitcode = 0;
	home = get_env(env, "HOME");
	if (command[1] == NULL || ft_strncmp(command[1], "~", 2) == 0)
	{
		if (!home)
		{
			pipex->exitcode = EXIT_FAILURE;
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		}
		chdir(home);
	}
	else if (ft_strncmp(command[1], "-", 1) == 0)
		return (ft_cd_oldpwd(pipex, env));
	else if (ft_strncmp(command[1], "~/", 2) == 0)
		return (ft_cd_use_home(home, command[1]));
	else if (checkpathexistence(command[1]) || ft_strncmp(command[1],
			"..", 3) == 0 || ft_strncmp(command[1], ".", 2) == 0)
		chdir(command[1]);
	else
		return (ft_cd_error(pipex, command[1]));
	update_pwd_env(pipex);
}

void	ft_cd_use_home(char *home, char *command)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(getenv(home), command + 1);
	chdir(temp);
	free(temp);
}

void	ft_cd_error(t_pipex *pipex, char *command)
{
	write(2, "minishell: cd: ", 16);
	write(2, command, ft_strlen(command));
	write(2, ": No such file or directory\n", 29);
	pipex->exitcode = 1;
}

void	ft_cd_oldpwd(t_pipex *pipex, char **env)
{
	char	*temp;

	temp = get_env(env, "OLDPWD");
	if (checkpathexistence(temp))
		ft_cd_error(pipex, temp);
	if (!temp)
	{
		pipex->exitcode = EXIT_FAILURE;
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2));
	}
	ft_printf("%s\n", temp);
	chdir(temp);
}

int	checkpathexistence(const char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == 0);
}
