/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 11:44:16 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 13:52:22 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **command, char **env, t_mini *mini)
{
	char	*home;

	mini->exitcode = 0;
	home = get_env(env, "HOME");
	if (command[1] == NULL || ft_strncmp(command[1], "~", 2) == 0)
	{
		if (!home)
		{
			mini->exitcode = EXIT_FAILURE;
			return (ft_putendl_fd("minishell: cd: HOME not set", 2));
		}
		chdir(home);
	}
	else if (ft_strncmp(command[1], "-", 1) == 0)
		return (ft_cd_oldpwd(mini));
	else if (ft_strncmp(command[1], "~/", 2) == 0)
		return (ft_cd_use_home(home, command[1]));
	else if (checkpathexistence(command[1]) || ft_strncmp(command[1],
			"..", 3) == 0 || ft_strncmp(command[1], ".", 2) == 0)
		chdir(command[1]);
	else
		return (ft_cd_error(mini, command[1]));
	update_pwd_env(mini);
}

void	ft_cd_use_home(char *home, char *command)
{
	char	*temp;

	temp = NULL;
	temp = ft_strjoin(getenv(home), command + 1);
	chdir(temp);
	free(temp);
}

void	ft_cd_error(t_mini *mini, char *command)
{
	write(2, "minishell: cd: ", 16);
	write(2, command, ft_strlen(command));
	write(2, ": No such file or directory\n", 29);
	mini->exitcode = 1;
}

void	ft_cd_oldpwd(t_mini *mini)
{
	char	*temp;

	temp = get_env(mini->env, "OLDPWD");
	if (!temp)
	{
		mini->exitcode = EXIT_FAILURE;
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2));
	}
	if (!checkpathexistence(temp))
	{
		ft_cd_error(mini, temp);
		return ;
	}
	ft_printf("%s\n", temp);
	chdir(temp);
}

int	checkpathexistence(const char *path)
{
	struct stat	buffer;

	return (stat(path, &buffer) == 0);
}
