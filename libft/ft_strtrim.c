/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:34:47 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:54:34 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_trim_possible(char c, char const *set)
{
	int		count;

	count = 0;
	while (set[count])
	{
		if (set[count] == c)
			return (1);
		count++;
	}
	return (0);
}

static int	ft_get_size(char const *s1, char const *set)
{
	int		count;
	int		size;

	size = ft_strlen(s1);
	count = 0;
	while (ft_is_trim_possible(s1[size - count - 1], set))
		count++;
	return (size - count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		count;
	int		size;
	char	*tab;

	count = 0;
	size = 0;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	while (ft_is_trim_possible(s1[count], set))
		count++;
	if (count == (int)ft_strlen(s1))
		return (ft_strdup(""));
	size = ft_get_size(s1 + count, set) + 1;
	tab = (char *)malloc((size) * sizeof(char));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s1 + count, size);
	return (tab);
}

/* int main() {
    // Example usage of ft_strtrim
    char *s1 = "mmaes   example string with spaces   mas";
    char *set = "mas";
    
    // Trim the string
    char *trimmed_string = ft_strtrim(s1, set);

    // Output the original and trimmed strings
    printf("Original string: \"%s\"\n", s1);
    printf("Trimmed string: \"%s\"\n", trimmed_string);

    // Free dynamically allocated memory
    free(trimmed_string);

    return 0;
}
 */