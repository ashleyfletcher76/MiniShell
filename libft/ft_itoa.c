/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:29:22 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/17 09:52:39 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	basamak_sayar(int n)
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
}*/

char	*ft_itoa(int n)
{
	char		*str;
	int			basamak;
	long int	new;

	new = n;
	basamak = basamak_sayar(n);
	if (n < 0)
	{
		new = new * -1;
		basamak++;
	}
	str = (char *) malloc((basamak + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[basamak] = 0;
	while (basamak > 0)
	{
		str[basamak - 1] = new % 10 + '0';
		new /= 10;
		basamak--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/* int main()
{

	printf("%s",ft_itoa(0));

	return (0);
	 
} */
