/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointerprint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:40:25 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:34 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	basamak_sayar_ptr(unsigned long long n)
{
	int	basamak;

	basamak = 0;
	while (n != 0)
	{
		n /= 16;
		basamak++;
	}
	return (basamak);
}

int	hexatransformlowerpointer(unsigned long long n)
{
	if (n >= 16)
	{
		hexatransformlowerpointer(n / 16);
		hexatransformlowerpointer(n % 16);
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
			if (ft_putchar_fd_print(n + 55 + 32, 1) == -1)
				return (-1);
		}
	}
	return (0);
}

int	ft_pointerprint(unsigned long long n)
{
	int	x;

	x = 0;
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (n == 0)
		x++;
	x += basamak_sayar_ptr(n);
	if (hexatransformlowerpointer(n) == -1)
		return (-1);
	return (x + 2);
}

/* int main()
{
    int *x;
	int y;
	y = 6;

	x = &y;
	int result;
    result = ft_printf("%p ", 15);
	ft_printf("\n%d",result);

	
   return (0);
} */