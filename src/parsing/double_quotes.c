/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:42:40 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/24 15:06:16 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parse_double_quote(t_mini *mini, int *i)
{
	char	*quoted_str;

	quoted_str = NULL;
	(*i)++;
	if (mini->prompt[*i] == '\"')
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
	if (mini->prompt[*i] == '\"' && mini->prompt[*i] == ' ' && mini->prompt[*i + 1] != '\0' && mini->prompt[*i + 1] != '\"' && mini->prompt[*i + 1] != '\'')
		(*i)++;
	return (quoted_str);
}

char	*dquote_helper(char *quoted_str)
{
	char	*temp1;
	char	*temp2;
	char	*new_str;
	char	*new_quoted;

	temp2 = ft_strdup("");
	new_str = quoted_str;
	while (1)
	{
		temp1 = readline("dquote> ");
		if (!temp1)
			break ;
		temp1 = ft_strjoin("\n", temp1);
		temp2 = ft_strchr(temp1, '\"');
		if (temp2)
			*temp2 = '\0';
		new_quoted = ft_strjoin(new_str, temp1);
		free (new_str);
		new_str = new_quoted;
		free(temp1);
		if (temp2)
			break ;
	}
	return (new_str);
}
