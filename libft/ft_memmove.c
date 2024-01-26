/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:48:54 by muhakose          #+#    #+#             */
/*   Updated: 2023/10/14 14:59:03 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*ptrdst;
	const unsigned char	*ptrsrc;

	if (!dst && !src)
		return (0);
	i = 0;
	ptrdst = (unsigned char *)dst;
	ptrsrc = (const unsigned char *)src;
	if (ptrdst < ptrsrc)
	{
		while (i < len)
		{
			ptrdst[i] = ptrsrc[i];
			i++;
		}
	}
	else
	{
		while (i < len--)
			ptrdst[len] = ptrsrc[len];
	}
	return (dst);
}

/* int main() {
    char str[] = "Hello, World!";
    char* src = str + 6;  // Points to "World!"
    char* dst = str + 1;  // Points to the space after 'H'
    size_t len = 7;

    printf("Before memmove:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dst);

    // Call your ft_memmove function here
    ft_memmove(dst, src, len);

    printf("\nAfter memmove:\n");
    printf("Source: %s\n", src);
    printf("Destination: %s\n", dst);

    return 0;
} */