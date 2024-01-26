/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexatransformupper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:30:28 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:56 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	hexatransformupper(unsigned int n)
{
	int		size;

	size = basamak_sayar_base16(n);
	if (n >= 16)
	{
		if (hexatransformupper(n / 16) == -1)
			return (-1);
		if (hexatransformupper(n % 16) == -1)
			return (-1);
	}
	else
	{
		if (n < 10)
		{
			if (ft_putchar_fd_print(n + 48, 1) == -1)
				return (-1);
		}
		else if (n >= 10)
		{
			if (ft_putchar_fd_print(n + 55, 1) == -1)
				return (-1);
		}
	}
	return (size);
}
