/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:09:26 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 13:47:01 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_counter(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (count);
}

static char	*wordup(const char *s, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *) malloc((finish - start + 1) * sizeof(char));
	if (word == NULL)
		return (0);
	while (start < finish)
	{
		word[i++] = s[start++];
	}
	word[i] = '\0';
	return (word);
}

static char	**free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
	return (NULL);
}

static char	**split2(const char *s, char c, char **new)
{
	size_t	i;
	size_t	j;
	int		index;

	index = -1;
	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			new[j] = wordup(s, index, i);
			if (!new[j])
				return (free_array(j, new));
			j++;
			index = -1;
		}
		i++;
	}
	new[j] = 0;
	return (new);
}

char	**ft_split(const char *s, char c)
{
	char	**new;

	new = (char **)malloc((word_counter(s, c) + 1) * sizeof(char *));
	if (!s || !(new))
		return (0);
	new = split2(s, c, new);
	return (new);
}
