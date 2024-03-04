/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_and_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 07:42:07 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/04 07:43:27 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_dollor(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (TRUE);
	return (FALSE);
}

int	token_dollor_first(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_')
		return (TRUE);
	return (FALSE);
}

int	if_check(char *s, char *p)
{
	int	i;

	i = 0;
	while (s[i] && p[i])
	{
		if (s[i] == '=' || p[i] == '=' || (p[i + 1] == '=' && p[i] == '+'))
			break ;
		if (s[i] != p[i])
			return (FALSE);
		i++;
	}
	if (p[i] == '\0' && (s[i] == '=' || s[i] == '\0'))
		return (TRUE);
	if (s[i] != '=' || p[i] != '=')
		return (FALSE);
	return (TRUE);
}
