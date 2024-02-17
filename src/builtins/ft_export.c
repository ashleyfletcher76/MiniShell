/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:57:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/17 10:13:46 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(char **commands, char **env, t_pipex *pipex)
{
	int i;
	int	equl_cnt;

	i = 0;
	if (commands[1] == NULL)
	{
		ft_export_print(env);
		return ;
	}
	if (ft_export_error(commands, env) == 1)
		return ;
	equl_cnt = ft_count_equal(commands[1]);
	while(env[i] != NULL && equl_cnt != 0)
	{
		if (ft_strncmp(env[i], commands[1], equl_cnt) == 0)
		{
			ft_strcpy(env[i], commands[1]);
			return ;
		}
		i++;
	}
	ft_export_helper(commands, env, equl_cnt);
	pipex->exitcode = 0;
}

int	ft_export_error(char **commands, char **env)
{
	if (ft_export_command_check(commands[1]) == FALSE)
		return (ft_put3endl_fd("export", ": not valid in this context: ", commands[1], 2), 1);
	else if (ft_export_command_check(commands[1]) == 2)
		return (ft_put3endl_fd("export", ": not an identifier: ", commands[1], 2), 1);
	if (commands[2] != NULL)
	{
		if (ft_export_error_helper(commands, env) == 1)
			return (1);
	}
	return (0);
}

int	ft_export_error_helper(char **commands, char **env)
{
	int		equal_cnt;
	int		equal_cnt2;
	int		i;
	char	*temp;

	i = 0;
	equal_cnt = ft_count_equal(commands[1]);
	equal_cnt2 = ft_count_equal(commands[2]);
	if (equal_cnt == 0 && equal_cnt2 != 0)
	{
		temp = ft_strjoin (commands[2],commands[1]);
		while(env[i] != NULL)
		{
			if (ft_strncmp(env[i], commands[2], equal_cnt2) == 0)
			{
				ft_strcpy(env[i], temp);
				free(temp);
				return (1);
			}
			i++;
		}
		env[i] = env[i - 1];
		env[i - 1] = temp;
		env[i + 1] = NULL; 
		return (1);
	}
	return (0);
}

