/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:15:51 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:40 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar_fd_print(int c, int fd)
{
	char	cd;

	cd = c;
	if (write(fd, &cd, 1) == -1)
		return (-1);
	return (1);
}
