/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:49:58 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:32 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	p = (void *)malloc((count) * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}

/* int main() {
	int *arr;
	size_t num_elements = 5;
	size_t element_size = sizeof(int);

	arr = (int *)ft_calloc(num_elements, element_size);

	if (arr == NULL) {
		printf("Memory allocation failed.\n");
		return 1;
    }

	free(arr);

	return 0;
}
*/