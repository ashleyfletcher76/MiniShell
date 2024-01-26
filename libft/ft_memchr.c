/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:09:09 by muhakose          #+#    #+#             */
/*   Updated: 2023/10/14 15:05:02 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}

/* int main() {
    int tab[7] = {-49, 49, 1, -1, 0, -2, 2};
    int *result = (int *)ft_memchr(tab, -1, sizeof(tab) / sizeof(tab[0]));

    if (result != NULL) {
        printf("Value found: %d\n", *result);
    } else {
        printf("Value not found\n");
    }

    return 0;
}
 */