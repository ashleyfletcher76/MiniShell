/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:32:52 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:42 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	basamak_sayar(int n)
{
	int	basamak;

	if (n == 0)
		return (1);
	basamak = 0;
	while (n != 0)
	{
		n /= 10;
		basamak++;
	}
	return (basamak);
}

int	ft_putnbr_fd_print(int n, int fd)
{
	if (n < 0)
	{
		if (ft_putchar_fd_print('-', fd) == -1)
			return (-1);
		n *= -1;
	}
	if (n >= 10)
	{
		if (ft_putnbr_fd_print(n / 10, fd) == -1)
			return (-1);
		if (ft_putnbr_fd_print(n % 10, fd) == -1)
			return (-1);
	}
	if (n < 10)
	{
		if (ft_putchar_fd_print(n + 48, fd) == -1)
			return (-1);
	}
	return (1);
}

int	nbrprinter(int n)
{
	size_t	size;

	if (n == -2147483648)
	{
		if (ft_putstr_fd_print("-2147483648", 1) == -1)
			return (-1);
		return (11);
	}
	size = 0;
	size = basamak_sayar(n);
	if (n < 0)
		size++;
	if (ft_putnbr_fd_print(n, 1) == -1)
		return (-1);
	return (size);
}
