/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:49:43 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 13:27:01 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	i = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen <= dstsize)
		srclen += dstlen;
	else
		srclen += dstsize;
	while (src[i] && dstlen + 1 < dstsize)
	{
		dst[dstlen++] = src[i++];
	}
	dst[dstlen] = '\0';
	return (srclen);
}
