/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:42:40 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 14:21:06 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_double_quote(t_mini *mini, int *i)
{
	char	*quoted_str;

	quoted_str = NULL;
	if (mini->prompt[++(*i)] == '\"')
		return (ft_strdup(""));
	while (mini->prompt[*i] != '\"' && mini->prompt[*i] != '\0')
	{
		if (mini->prompt[*i] == '$')
			quoted_str = dollar_inside_quotes(mini, i, quoted_str);
		else
		{
			quoted_str = ft_char_join(quoted_str, mini->prompt[*i]);
			if (mini->prompt[*i] != '\"')
				(*i)++;
		}
	}
	if (mini->prompt[*i] == '\0')
	{
		if (!quoted_str)
			quoted_str = ft_strdup("");
		quoted_str = dquote_helper(quoted_str);
	}
	return (quoted_str);
}

char	*dquote_helper(char *quoted_str)
{
	char	*temp1;
	char	*temp2;

	while (1)
	{
		temp1 = readline("dquote> ");
		if (!temp1)
		{
			free(temp1);
			break ;
		}
		temp1 = ft_strjoin_freeself(ft_strdup("\n"), temp1);
		temp2 = ft_strchr(temp1, '\"');
		if (temp2)
			*temp2 = '\0';
		quoted_str = ft_strjoin_freeself(quoted_str, temp1);
		if (temp2)
			break ;
	}
	return (quoted_str);
}
