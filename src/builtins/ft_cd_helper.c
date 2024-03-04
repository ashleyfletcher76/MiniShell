/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:51:48 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/04 10:22:58 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_env(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*temp;
	int		i;

	temp = NULL;
	i = 0;
	if (get_env(mini->env, "PWD"))
	{
		temp = ft_strdup(get_env(mini->env, "PWD"));
		update_oldpwd_env(mini, temp);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (get_env(mini->env, "PWD") != NULL)
			update_pwd_envhelp(mini, cwd);
		else
		{
			while (mini->env[i])
				i++;
			mini->env = ft_realloc_char(mini->env, i);
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("PWD=", cwd);
			mini->env[i + 1] = NULL;
		}
	}
}

void	update_pwd_envhelp(t_mini *mini, char *cwd)
{
	int	i;

	i = 0;
	while (mini->env[i] != NULL)
	{
		if (ft_strncmp(mini->env[i], "PWD=", 4) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("PWD=", cwd);
			break ;
		}
		i++;
	}
}

void	update_oldpwd_env(t_mini *mini, char *temp)
{
	int		i;

	i = 0;
	if (get_env(mini->env, "OLDPWD"))
	{
		while (mini->env[i] != NULL)
		{
			if (ft_strncmp(mini->env[i], "OLDPWD=", 7) == 0)
			{
				free(mini->env[i]);
				mini->env[i] = ft_strjoin("OLDPWD=", temp);
				break ;
			}
			i++;
		}
	}
	else
		update_oldpwd_env_part_2(mini, temp, i);
	if (temp != NULL)
		free(temp);
}

void	update_oldpwd_env_part_2(t_mini *mini, char *temp, int i)
{
	while (mini->env[i])
		i++;
	mini->env = ft_realloc_char(mini->env, i);
	free(mini->env[i]);
	mini->env[i] = ft_strjoin("OLDPWD=", temp);
	mini->env[i + 1] = NULL;
}
