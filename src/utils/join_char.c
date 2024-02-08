/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:37:39 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/08 17:24:59 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_char_join(char *s1, char c)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	total_len;

	if (s1 == NULL)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	len2 = 1;
	total_len = len1 + len2 + 1;
	result = (char *)malloc(total_len);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(result, s1);
	result[len1] = c;
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}
