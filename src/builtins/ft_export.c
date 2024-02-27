/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:57:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 19:31:37 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **commands, char **env, t_pipex *pipex)
{
	int	i;
	int	flag;

	i = 0;
	if (commands[1] == NULL)
	{
		ft_export_print(env);
		pipex->exitcode = EXIT_SUCCESS;
		return ;
	}
	flag = ft_export_error(pipex, commands);
	if (flag == FALSE)
		return ;
	else if (flag == 2)
		append_export(commands, env);
	else
		normal_export(commands, env);
	pipex->exitcode = EXIT_SUCCESS;
}

void	append_export(char **comds, char **env)
{
	char	*var;
	char	*val;
	int		equal;
	int		i;

	i = 0;
	equal = ft_count_equal(comds[1]) - 2;
	if (equal == -2)
		return ;
	if (ft_strchr(comds[1], '=') != NULL)
		val = ft_strdup(ft_strchr(comds[1], '=') + 1);
	var = malloc (sizeof(char) * equal);
	var = ft_strncpy(var, comds[1], equal);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, equal - 1) == 0)
		{
			free(var);
			env[i] = ft_strjoin_freeself(env[i], val);
			return ;
		}
		i++;
	}
	ft_export_helper(comds, env, var);
}

void	normal_export(char **comds, char **env)
{
	int		equal;
	int		i;

	i = 0;
	equal = ft_count_equal(comds[1]) - 1;
	if (equal == -1)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], comds[1], equal) == 0)
		{
			free(env[i]);
			env[i] = ft_strdup(comds[1]);
			return ;
		}
		i++;
	}
	ft_export_helper(comds, env, NULL);
}

void	ft_export_helper(char **commands, char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	if (var != NULL && env[i] == NULL)
	{
		env[i] = env[i - 1];
		env[i - 1] = ft_strjoin(var, ft_strchr(commands[1], '='));
		env[i + 1] = NULL;
	}
	if (var == NULL && env[i] == NULL)
	{
		env[i] = env[i - 1];
		env[i - 1] = commands[1];
		env[i + 1] = NULL;
	}
	(void)var;
}

int	ft_export_error(t_pipex *pipex, char **commands)
{
	int	flag;

	flag = check_variable(commands[1]);
	if (flag == FALSE)
	{
		export_error_message(pipex, commands, 0);
	}
	return (flag);
}
