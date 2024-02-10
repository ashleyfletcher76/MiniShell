/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:42:33 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/10 11:17:54 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_single_quote(t_mini *mini, int *j, int *i)
{
	char	*quoted_str;

	quoted_str = NULL;
	(*i)++;
	while (mini->prompt[*i] != '\'' && mini->prompt[*i] != '\0')
	{
		quoted_str = ft_char_join(quoted_str, mini->prompt[*i]);
		(*i)++;
	}
	if (mini->prompt[*i] == '\0')
		quoted_str = quote_helper(quoted_str);
	mini->commands[0].cmd_args[*j] = ft_strdup(quoted_str);
	(*j)++;
	if (quoted_str)
	{
		free (quoted_str);
		quoted_str = NULL;
	}
	if (mini->prompt[*i] == '\'')
		(*i)++;
}

char	*quote_helper(char *quoted_str)
{
	char	*temp1;
	char	*temp2;
	char	*new_str;
	char	*new_quoted;

	temp2 = ft_strdup("");
	new_str = quoted_str;
	while (1)
	{
		temp1 = readline("quote> ");
		if (!temp1)
			break ;
		temp2 = ft_strchr(temp1, '\'');
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
