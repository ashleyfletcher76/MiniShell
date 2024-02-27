/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/27 14:54:52 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_dollor(char c)
{
	char	*token;
	int		i;

	i = 0;
	token = " \t\'\"=$:-\0|/";
	while (i < 12)
	{
		if (token[i] == c)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*handle_dollar(t_mini *mini, int *i)
{
	char	*new_temp;
	char	*exit_code;

	new_temp = NULL;
	if (mini->prompt[*i] == '$')
	{
		if (mini->prompt[*i + 1] == '\"')
			return (NULL);
		if (skip_whitespace(mini->prompt[*i + 1]))
			return (ft_strdup("$"));
		if (mini->prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			return (exit_code);
		}
		(*i)++;
		while (token_dollor(mini->prompt[*i]))
			new_temp = ft_char_join(new_temp, mini->prompt[(*i)++]);
	}
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
		if (skip_whitespace(mini->prompt[*i]) || mini->prompt[*i] == '\"')
		{
			if (!quoted_str)
				quoted_str = ft_strdup("");
			return (ft_char_join(quoted_str, '$'));
		}
		temp_env = dollar_quotes_helper(mini, temp_env, i);
	}
	if (!get_env(mini->env, temp_env))
		return (quoted_str);
	temp_env = ft_strdup(get_env(mini->env, temp_env));
	quoted_str = ft_strjoin_freeself(quoted_str, temp_env);
	return (quoted_str);
}

char	*dollar_quotes_helper(t_mini *mini, char *temp_env, int *i)
{
	while (token_dollor(mini->prompt[*i]))
	{
		temp_env = ft_char_join(temp_env, mini->prompt[*i]);
		if (token_dollor(mini->prompt[*i]))
			(*i)++;
	}
	return (temp_env);
}
