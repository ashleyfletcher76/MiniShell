/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/19 15:26:27 by muhakose         ###   ########.fr       */
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
		return (NULL);
	new_temp = ft_strdup(getenv(new_temp));
	return (new_temp);
}

char	*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str)
{
	quoted_str = ft_strjoin_freeself(quoted_str, handle_dollar(mini, i));
	return (quoted_str);
}
