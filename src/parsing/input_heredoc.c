/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:03:30 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 12:26:17 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_expand_heredoc(t_mini *mini, char *temp)
{
	int		i;
	char	*new_temp;

	i = 0;
	new_temp = NULL;
	if (mini->expand_heredoc == 0)
	{
		while (temp[i])
		{
			if (temp[i] == '$')
			{
				new_temp = ft_strjoin_freeself(new_temp,
						handle_dollar_heredoc(mini, temp, &i));
				if (temp[i] != '\0')
					i++;
			}
			if (temp[i] != '\0')
				new_temp = ft_char_join(new_temp, temp[i++]);
		}
		free (temp);
		return (new_temp);
	}
	return (temp);
}

char	*handle_dollar_heredoc(t_mini *mini, char *prompt, int *i)
{
	char	*new_temp;
	char	*exit_code;
	char	*give_back;

	new_temp = NULL;
	if (prompt[*i] == '$')
	{
		if (prompt[*i + 1] == '\"' || prompt[*i + 1] == '\'')
			return (NULL);
		if (skip_whitespace(prompt[*i + 1]))
			return (ft_strdup("$"));
		if (prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			return (exit_code);
		}
		new_temp = dollar_helper_here(i, new_temp, prompt);
	}
	(*i)--;
	if (!get_env(mini->env, new_temp))
		return (free(new_temp), NULL);
	give_back = ft_strdup(get_env(mini->env, new_temp));
	free(new_temp);
	return (give_back);
}

char	*dollar_helper_here(int *i, char *new_temp, char *prompt)
{
	(*i)++;
	while (token_dollor(prompt[*i]))
		new_temp = ft_char_join(new_temp, prompt[(*i)++]);
	return (new_temp);
}

char	*parse_double_heredoc(t_mini *mini, int *i)
{
	char	*quoted_str;

	quoted_str = NULL;
	if (mini->prompt[++(*i)] == '\"')
		return (ft_strdup(""));
	while (mini->prompt[*i] != '\"' && mini->prompt[*i] != '\0')
	{
		quoted_str = ft_char_join(quoted_str, mini->prompt[*i]);
		(*i)++;
	}
	if (mini->prompt[*i] == '\0')
	{
		if (!quoted_str)
			quoted_str = ft_strdup("");
		quoted_str = quote_helper(quoted_str);
	}
	return (quoted_str);
}
