/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 09:32:54 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;
	int	exit_code;

	i = 1;
	if (commands[1] == NULL)
	{
		pipex->exitcode = EXIT_SUCCESS;
		return ;
	}
	while (commands[i])
	{
		exit_code = ft_unset_loop(commands[i], env, pipex);
		if (exit_code == 1)
			pipex->exitcode = exit_code;
		i++;
	}
	if (pipex->exitcode != 1)
		pipex->exitcode = exit_code;
}

int	ft_unset_loop(char *commands, char **env, t_pipex *pipex)
{
	int		i;
	int		count_eql;

	i = 0;
	count_eql = ft_count_equal2(commands);
	if (count_eql == -1)
		return (export_error_message(pipex, commands, 1), 1);
	if (check_variable(commands) == FALSE)
		return (export_error_message(pipex, commands, 1), 1);
	while (env[i])
	{
		if (ft_strncmp(env[i], commands, count_eql) == 0)
		{
			free(env[i]);
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i - 1] = NULL;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
