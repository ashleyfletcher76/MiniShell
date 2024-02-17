/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/17 12:57:14 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_equal2(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (-1);
		i++;
	}
	return (i);
}

void	ft_unset(char **commands, char **env, t_pipex *pipex)
{
	int		i;
	int		count_eql;

	i = 0;
	if (commands[1] == NULL)
	{
		pipex->exitcode = EXIT_FAILURE;
		return (ft_putendl_fd("unset: not enough arguments", 2));
	}
	count_eql = ft_count_equal2(commands[1]);
	if (count_eql == -1 )
	{
		pipex->exitcode = EXIT_FAILURE;
		return (ft_put3endl_fd("unset: ", commands[1], ": invalid parameter name", 2));
	}
	if (ft_export_command_check(commands[1]) == FALSE || ft_export_command_check(commands[1]) == 2)
	{
		pipex->exitcode = EXIT_FAILURE;
		return (ft_put3endl_fd("unset: ", commands[1], ": invalid parameter name", 2));
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], commands[1], count_eql) == 0)
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i - 1] = NULL;
			return ;
		}
		i++;
	}
	pipex->exitcode = EXIT_SUCCESS;
}
