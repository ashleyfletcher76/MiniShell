/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/17 13:47:21 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_dollar(t_mini *mini, int*i, int *j, t_commands **cmd)
{
	char	*new_temp;
	char	*exit_code;

	new_temp = NULL;
	if (mini->prompt[*i] == '$')
	{
		if (mini->prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			(*cmd)->cmd_args[*j] = exit_code;
			return ;
		}
		(*i)++;
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0')
		{
			new_temp = ft_char_join(new_temp, mini->prompt[*i]);
			(*i)++;
		}
	}
	new_temp = getenv(new_temp);
	(*cmd)->cmd_args[*j] = ft_strdup(new_temp);
	(*j)++;
}

char	*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str)
{
	char	*temp_env;
	char	*new_temp;

	temp_env = NULL;
	if (mini->prompt[*i] == '$')
	{
		(*i)++;
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0')
		{
			if (mini->prompt[*i + 1] == '\'')
			{
				temp_env = ft_char_join(temp_env, mini->prompt[*i]);
				new_temp = ft_strdup(temp_env);
				temp_env = getenv(new_temp);
				printf("new temp = %s\n", new_temp);
				new_temp = ft_strjoin(quoted_str, temp_env);
				return (new_temp);
			}
			temp_env = ft_char_join(temp_env, mini->prompt[*i]);
			(*i)++;
		}
	}
	temp_env = getenv(temp_env);
	quoted_str = ft_strjoin(quoted_str, temp_env);
	return (quoted_str);
}
