/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:56:02 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/29 16:26:31 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f'
		|| c == '\v' || c == '\r' || c == '\0')
		return (TRUE);
	return (FALSE);
}

int	no_whitespace_skip(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f'
		|| c == '\v' || c == '\r' || c == '\0')
		return (FALSE);
	return (TRUE);
}

int	skip_quotes(char *s, int i)
{
	if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"' && s[i + 1] != '\0')
			i++;
	}
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i + 1] != '\0')
			i++;
	}
	return (i);
}
