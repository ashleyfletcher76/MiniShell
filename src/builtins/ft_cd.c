/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:44:16 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/24 16:22:02 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checkPathExistence(const char *path)
{
	struct stat buffer;

	return (stat(path, &buffer) == 0);
}

void	ft_cd(char **command, char **env, t_pipex *pipex)
{
	char	*home;
	char	*temp;

	pipex->exitcode = 0;
	home = get_env(env, "HOME");
	if (command[1] == NULL || ft_strncmp(command[1], "~", 2) == 0 )
	{
		if (!home)
		{
			pipex->exitcode = EXIT_FAILURE;
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		}
		chdir(home);
	}
	else if (ft_strncmp(command[1], "~/", 2) == 0)
	{
		temp = ft_strjoin(getenv(home), command[1] + 1);
		chdir(temp);
		free(temp);
	}
	else if (checkPathExistence(command[1]) || ft_strncmp(command[1], "..", 3) == 0 || ft_strncmp(command[1], ".", 2) == 0)
		chdir(command[1]);
	else
	{
		write(2, "cd: no such file or directory: ", 32);
		ft_putendl_fd(command[1], 2);
		pipex->exitcode = 1;
		return ;
	}
	update_pwd_env(pipex);
}

void	update_pwd_env(t_pipex *pipex)
{
	char	cwd[1024];
	char	*temp;
	int		i;
	
	i = 0;
	temp = ft_strdup(get_env(pipex->env, "PWD"));
	if (!temp)
		temp = ft_strdup("");
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (get_env(pipex->env, "PWD") != NULL)
		{
			while (pipex->env[i] != NULL)
			{
				if (ft_strncmp(pipex->env[i], "PWD=", 4) == 0)
				{
					ft_strncpy(pipex->env[i], ft_strjoin("PWD=", cwd), ft_strlen(cwd) + 5);
					break ;
				}
				i++;
			}
		}
		else
		{
			while (pipex->env[i])
				i++;
			pipex->env[i] = ft_strdup(ft_strjoin("PWD=", cwd));
			pipex->env[i + 1] = NULL;
		}
	}
	update_oldpwd_env(pipex, temp);
}

void	update_oldpwd_env(t_pipex *pipex, char *temp)
{
	int		i;

	i = 0;
	if (get_env(pipex->env, "OLDPWD"))
	{
		while (pipex->env[i] != NULL)
		{
			if (ft_strncmp(pipex->env[i], "OLDPWD=", 7) == 0)
			{
				ft_strncpy(pipex->env[i] + 7, temp, ft_strlen(temp) + 1);
				break ;
			}
			i++;
		}
	}
	else
	{
		while(pipex->env[i])
			i++;
		pipex->env[i] = ft_strdup(ft_strjoin("OLDPWD=", temp));
		pipex->env[i + 1] = NULL;
	}
	free(temp);
}
