/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 14:04:47 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/27 11:54:28 by asfletch         ###   ########.fr       */
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

char	**ft_realloc_double_char(char **ptr, int j)
{
	char	**new_ptr;
	int i = 0;

	if (ptr == NULL)
	{
		ptr = malloc(sizeof(char *) * 2);
		return (ptr);
	}
	new_ptr = malloc(sizeof(char *) * (j + 2));
	while (ptr[i])
	{
		new_ptr[i] = ft_strdup(ptr[i]);
		i++;
	}
	new_ptr[i] = NULL;
	free_double_array(ptr);
	return (new_ptr);
}

int	*ft_realloc_int(int *ptr, int j)
{
	int	*new_ptr;
	int	i;

	i = 0;
	if (!ptr)
	{
		ptr = malloc(sizeof(int) * 2);
		return (ptr);
	}
	new_ptr = malloc(sizeof(int) * (j + 2));
	while (ptr[i])
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	new_ptr[i] = 0;
	free (ptr);
	return (new_ptr);
}
