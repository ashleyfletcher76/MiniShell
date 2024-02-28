/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:51:48 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 10:09:53 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			update_pwd_envhelp(pipex, cwd);
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

void	update_pwd_envhelp(t_pipex *pipex, char *cwd)
{
	int	i;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		if (ft_strncmp(pipex->env[i], "PWD=", 4) == 0)
		{
			ft_strncpy(pipex->env[i], ft_strjoin("PWD=", cwd),
				ft_strlen(cwd) + 5);
			break ;
		}
		i++;
	}
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
		while (pipex->env[i])
			i++;
		pipex->env[i] = ft_strdup(ft_strjoin("OLDPWD=", temp));
		pipex->env[i + 1] = NULL;
	}
	free(temp);
}
