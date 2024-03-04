/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/04 07:42:25 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar(t_mini *mini, int *i)
{
	char	*new_temp;
	char	*exit_code;
	char	*give_back;

	new_temp = NULL;
	if (mini->prompt[*i] == '$')
	{
		if (mini->prompt[*i + 1] == '\"' || mini->prompt[*i + 1] == '\'')
			return (NULL);
		if (skip_whitespace(mini->prompt[*i + 1]))
			return (ft_strdup("$"));
		if (mini->prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			return (exit_code);
		}
		new_temp = dollar_helper(mini, i, new_temp);
	}
	(*i)--;
	if (!get_env(mini->env, new_temp))
		return (free(new_temp), NULL);
	give_back = ft_strdup(get_env(mini->env, new_temp));
	free(new_temp);
	return (give_back);
}

char	*dollar_helper(t_mini *mini, int *i, char *new_temp)
{
	(*i)++;
	if (mini->prompt[*i] == '$')
		return (ft_strdup("$"));
	if (token_dollor_first(mini->prompt[*i]) == FALSE)
	{
		new_temp = ft_char_join(new_temp, mini->prompt[(*i)++]);
		return (new_temp);
	}
	while (token_dollor(mini->prompt[*i]))
		new_temp = ft_char_join(new_temp, mini->prompt[(*i)++]);
	return (new_temp);
}

char	*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str)
{
	char	*temp_env;

	temp_env = NULL;
	if (mini->prompt[*i] == '$')
	{
		(*i)++;
		if (mini->prompt[*i] == '?')
			return ((*i)++, ft_strjoin_freeself(quoted_str,
					ft_itoa(mini->exitcode)));
		if (skip_whitespace(mini->prompt[*i]) || mini->prompt[*i] == '\"')
		{
			if (!quoted_str)
				quoted_str = ft_strdup("");
			return (ft_char_join(quoted_str, '$'));
		}
		temp_env = dollar_quotes_helper(mini, temp_env, i);
	}
	if (!get_env(mini->env, temp_env))
		return (free (temp_env), quoted_str);
	quoted_str = ft_strjoin_freeself(quoted_str,
			ft_strdup(get_env(mini->env, temp_env)));
	free (temp_env);
	return (quoted_str);
}

char	*dollar_quotes_helper(t_mini *mini, char *temp_env, int *i)
{
	if (mini->prompt[*i] == '$')
		return (ft_strdup("$"));
	if (token_dollor_first(mini->prompt[*i]) == FALSE)
	{
		temp_env = ft_char_join(temp_env, mini->prompt[(*i)++]);
		return (temp_env);
	}
	while (token_dollor(mini->prompt[*i]))
	{
		temp_env = ft_char_join(temp_env, mini->prompt[*i]);
		if (token_dollor(mini->prompt[*i]))
			(*i)++;
	}
	return (temp_env);
}
