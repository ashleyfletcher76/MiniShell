/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:57:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 14:05:57 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **commands, t_mini *mini)
{
	int	i;
	int	exit_code;

	i = 1;
	if (commands[1] == NULL)
	{
		ft_export_print(mini->env);
		mini->exitcode = EXIT_SUCCESS;
		return ;
	}
	while (commands[i])
	{
		exit_code = ft_export_loop(commands[i], mini);
		if (exit_code == 1)
			mini->exitcode = exit_code;
		i++;
	}
	if (mini->exitcode != 1)
		mini->exitcode = exit_code;
}

int	ft_export_loop(char *commands, t_mini *mini)
{
	int	flag;

	flag = ft_export_error(mini, commands);
	if (flag == FALSE)
		return (EXIT_FAILURE);
	else if (flag == 2)
		append_export(commands, mini);
	else
		normal_export(commands, mini);
	return (EXIT_SUCCESS);
}

void	append_export(char *comds, t_mini *mini)
{
	char	*var;
	char	*val;
	int		equal;
	int		i;

	i = 0;
	equal = ft_count_equal(comds) - 2;
	if (equal == -2)
		return ;
	if (ft_strchr(comds, '=') != NULL)
		val = ft_strdup(ft_strchr(comds, '=') + 1);
	var = malloc (sizeof(char) * equal);
	var = ft_strncpy(var, comds, equal);
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], var, equal - 1) == 0)
		{
			free(var);
			mini->env[i] = ft_strjoin_freeself(mini->env[i], val);
			return ;
		}
		i++;
	}
	ft_export_helper(comds, mini, var);
	return (free(val), free(var));
}

void	normal_export(char *comds, t_mini *mini)
{
	int		equal;
	int		i;

	i = 0;
	equal = ft_count_equal(comds) - 1;
	if (equal == -1)
		return ;
	while (mini->env[i])
	{
		if (ft_strncmp(mini->env[i], comds, equal) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(comds);
			return ;
		}
		i++;
	}
	ft_export_helper(comds, mini, NULL);
}

void	ft_export_helper(char *commands, t_mini *mini, char *var)
{
	int	i;

	i = 0;
	while (mini->env[i])
		i++;
	if (var != NULL && mini->env[i] == NULL)
	{
		mini->env = ft_realloc_char(mini->env, i);
		free(mini->env[i]);
		mini->env[i] = mini->env[i - 1];
		mini->env[i - 1] = ft_strjoin(var, ft_strchr(commands, '='));
		mini->env[i + 1] = NULL;
	}
	if (var == NULL && mini->env[i] == NULL)
	{
		mini->env = ft_realloc_char(mini->env, i);
		free(mini->env[i]);
		mini->env[i] = mini->env[i - 1];
		mini->env[i - 1] = ft_strdup(commands);
		mini->env[i + 1] = NULL;
	}
}
