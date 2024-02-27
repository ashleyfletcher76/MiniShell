/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:55:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 18:32:09 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	total_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	total_len = len1 + len2 + 1;
	result = (char *)malloc(total_len);
	if (result == NULL)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	return (result);
}

static char	*strjoin_helper(char *remains, char *array, int *j)
{
	int	i;

	i = 0;
	while (remains[i])
		array[(*j)++] = remains[i++];
	return (array);
}

char	*ft_strjoin_freeself(char *remains, char *buffer)
{
	char			*array;
	unsigned int	size;
	int				i;
	int				j;

	if (!remains && !buffer)
		return (NULL);
	if (!remains)
		return (buffer);
	if (!buffer)
		return (remains);
	size = ft_strlen(remains) + ft_strlen(buffer);
	array = malloc (sizeof(char) * (size + 1));
	i = 0;
	j = 0;
	if (remains)
		strjoin_helper(remains, array, &j);
	while (buffer[i])
		array[j++] = buffer[i++];
	array[size] = '\0';
	if (remains)
		free ((void *)remains);
	if (buffer)
		free ((void *)buffer);
	return (array);
}
