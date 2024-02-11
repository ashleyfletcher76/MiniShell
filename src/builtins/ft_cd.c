/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:44:16 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/10 12:42:57 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checkPathExistence(const char *path)
{
	struct stat buffer;

	return (stat(path, &buffer) == 0);
}

void	ft_cd(char **command, char **env)
{
	char *home;
	char *temp;

	home = getenv("HOME");
	if (command[1] == NULL || ft_strncmp(command[1], "~", 2) == 0 )
		chdir(home);
	else if (ft_strncmp(command[1], "~/", 2) == 0)
	{
		temp = ft_strjoin(home, command[1] + 1);
		chdir(temp);
		free(temp);
	}
	else if (checkPathExistence(command[1]) || ft_strncmp(command[1], "..", 3) == 0 || ft_strncmp(command[1], ".", 2) == 0)
		chdir(command[1]);
	else
	{
		write(2, "cd: no such file or directory: ", 32);
		ft_putendl_fd(command[1], 2);
	}
	update_pwd_env(env);
}

void update_pwd_env(char **environ)
{
    char	cwd[1024];
	char	*temp;
	int		i;
	
	i = 0;
	temp = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		while (environ[i] != NULL)
		{
			if (ft_strncmp(environ[i], "PWD=", 4) == 0)
			{
				temp = ft_strdup(environ[i]);
				ft_strncpy(environ[i], ft_strjoin("PWD=", cwd), ft_strlen(cwd) + 5);
			}
			if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			{
				ft_strncpy(environ[i],  ft_strjoin("OLDPWD=", temp + 4), ft_strlen(temp) + 3);
				environ[i][ft_strlen(temp) + 3] = '\0';
			}
			i++;
		}
		free(temp);
	}
}
