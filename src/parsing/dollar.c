/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/18 16:12:37 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_dollar(t_mini *mini, int *i)
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
			return (exit_code);
		}
		(*i)++;
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0')
		{
			new_temp = ft_char_join(new_temp, mini->prompt[*i]);
			(*i)++;
		}
	}
	new_temp = ft_strdup(getenv(new_temp));
	return (new_temp);
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
				temp_env = ft_strdup(getenv(new_temp));
				new_temp = ft_strjoin(quoted_str, temp_env);
				return (new_temp);
			}
			temp_env = ft_char_join(temp_env, mini->prompt[*i]);
			(*i)++;
		}
	}
	temp_env = ft_strdup(getenv(temp_env));
	quoted_str = ft_strjoin(quoted_str, temp_env);
	return (quoted_str);
}
