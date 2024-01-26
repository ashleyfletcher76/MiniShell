/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexatransformlower.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:30:28 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:51 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	basamak_sayar_base16(unsigned int n)
{
	int	basamak;

	if (n == 0)
		return (1);
	basamak = 0;
	while (n != 0)
	{
		n /= 16;
		basamak++;
	}
	return (basamak);
}

int	hexatransformlower(unsigned int n)
{
	int		size;

	size = basamak_sayar_base16(n);
	if (n >= 16)
	{
		if (hexatransformlower(n / 16) == -1)
			return (-1);
		if (hexatransformlower(n % 16) == -1)
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
			if (ft_putchar_fd_print(n + 55 + 32, 1) == -1)
				return (-1);
		}
	}
	return (size);
}

/* int main()
{
    int x;

	int result;
    result = ft_printf("%X", -15);

	printf("\n%d",result);

	
   return (0);
} */
