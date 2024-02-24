/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/24 14:27:54 by muhakose         ###   ########.fr       */
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
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '\'' && mini->prompt[*i] != '\"' && mini->prompt[*i] != ':' && mini->prompt[*i] != '-')
		{
			new_temp = ft_char_join(new_temp, mini->prompt[*i]);
			(*i)++;
		}
	}
	if (mini->prompt[*i] == ' ' || mini->prompt[*i] == '\0' || mini->prompt[*i] == '\'' || mini->prompt[*i] == '\"' || mini->prompt[*i] == ':' || mini->prompt[*i] == '-')
		(*i)--;

	if (!get_env(mini->env, new_temp))
		return (NULL);
	new_temp = ft_strdup(get_env(mini->env, new_temp));
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
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '\'' && mini->prompt[*i] != '\"' && mini->prompt[*i] != ':' && mini->prompt[*i] != '-')
		{
			temp_env = ft_char_join(temp_env, mini->prompt[*i]);
			if (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0' && mini->prompt[*i] != '\'' && mini->prompt[*i] != '\"' && mini->prompt[*i] != ':' && mini->prompt[*i] != '-')
				(*i)++;
		}
	}
	if (!get_env(mini->env, temp_env))
		return (quoted_str);
	temp_env = ft_strdup(get_env(mini->env, temp_env));
	quoted_str = ft_strjoin_freeself(quoted_str, temp_env);
	return (quoted_str);
}
