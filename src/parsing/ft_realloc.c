/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:04:47 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/06 14:52:51 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	*allocate_and_zero(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		new_ptr = allocate_and_zero(new_size);
	else
	{
		new_ptr = allocate_and_zero(new_size);
		if (new_ptr)
		{
			if (old_size < new_size)
				copy_size = old_size;
			else
				copy_size = new_size;
			if (copy_size > 0)
			{
				ft_memcpy(new_ptr, ptr, copy_size);
				free (ptr);
			}
		}
	}
	return (new_ptr);
}
