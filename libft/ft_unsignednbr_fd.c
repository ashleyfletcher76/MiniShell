/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignednbr_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:27:01 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:48 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	basamak_sayar_print(unsigned int n)
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

int	ft_unsignednbr_fd_print(unsigned int n, int fd)
{
	if (n >= 10)
	{
		if (ft_unsignednbr_fd_print(n / 10, fd) == -1)
			return (-1);
		if (ft_unsignednbr_fd_print(n % 10, fd) == -1)
			return (-1);
	}
	if (n < 10)
	{
		if (ft_putchar_fd_print(n + 48, fd) == -1)
			return (-1);
	}
	return (1);
}

int	ft_unsignednbr_fd(unsigned int n)
{
	size_t	size;

	size = 0;
	size = basamak_sayar_print(n);
	if (ft_unsignednbr_fd_print(n, 1) == -1)
		return (-1);
	return (size);
}

/* int main()
{
    int x;

	int result;
    result = ft_printf("%u",-10);
	ft_printf("\n%d",result);

	
   return (0);
} */