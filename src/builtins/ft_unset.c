/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 12:25:21 by asfletch         ###   ########.fr       */
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

void	ft_unset(char **commands, char **env, t_mini *mini)
{
	int	i;
	int	exit_code;

	i = 1;
	if (commands[1] == NULL)
	{
		mini->exitcode = EXIT_SUCCESS;
		return ;
	}
	while (commands[i])
	{
		exit_code = ft_unset_loop(commands[i], env, mini);
		exit_code = ft_export_unset_loop(commands[i], mini);
		if (exit_code == 1)
			mini->exitcode = exit_code;
		i++;
	}
	if (mini->exitcode != 1)
		mini->exitcode = exit_code;
}

int	ft_unset_loop(char *commands, char **env, t_mini *mini)
{
	int		i;
	int		count_eql;

	i = 0;
	count_eql = ft_count_equal2(commands);
	if (count_eql == -1)
		return (export_error_message(mini, commands, 1), 1);
	if (check_variable(commands) == FALSE)
		return (export_error_message(mini, commands, 1), 1);
	while (env[i])
	{
		if (ft_strncmp(env[i], commands, ft_count_equal(env[i]) - 1) == 0)
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

int	ft_export_unset_loop(char *commands, t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->export[i])
	{
		if (ft_strncmp(mini->export[i] + 11, commands,
				ft_count_equal(mini->export[i]) - 12) == 0)
		{
			free(mini->export[i]);
			while (mini->export[i])
			{
				mini->export[i] = mini->export[i + 1];
				i++;
			}
			mini->export[i - 1] = NULL;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
