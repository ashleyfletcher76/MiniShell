/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/21 15:49:26 by asfletch         ###   ########.fr       */
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
		if (mini->prompt[*i + 1] == ' ' || mini->prompt[*i + 1] == '\0')
			return (ft_strdup("$"));
		if (mini->prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			return (exit_code);
		}
		(*i)++;
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '\'' && mini->prompt[*i] != '\"' && mini->prompt[*i] != ':')
		{
			new_temp = ft_char_join(new_temp, mini->prompt[*i]);
			(*i)++;
		}
	}
	if (mini->prompt[*i] == ':')
		(*i)--;
	if (!getenv(new_temp))
		return (ft_strdup(""));
	new_temp = ft_strdup(getenv(new_temp));
	return (new_temp);
}

char	*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str)
{
	char	*temp_env;

	temp_env = NULL;
	if (mini->prompt[*i] == '$')
	{
		(*i)++;
		if (!quoted_str)
			quoted_str = ft_strdup("");
		if (mini->prompt[*i] == '?')
				return ((*i)++, ft_strjoin(quoted_str, ft_itoa(mini->exitcode)));
		if (mini->prompt[*i] == ' ' || mini->prompt[*i] == '\0' || mini->prompt[*i] == '\"')
		{
			if (!quoted_str)
			 quoted_str	 = ft_strdup("");
			return (ft_char_join(quoted_str, '$'));
		}
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '\"')
		{
			temp_env = ft_char_join(temp_env, mini->prompt[*i]);
			if (mini->prompt[*i] != ' ')
				(*i)++;
		}
	}
	if (!getenv(temp_env))
		return (quoted_str);
	temp_env = ft_strdup(getenv(temp_env));
	quoted_str = ft_strjoin_freeself(quoted_str, temp_env);
	return (quoted_str);
}
