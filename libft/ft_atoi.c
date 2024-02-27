/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:35:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 10:59:52 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	iswhitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\f'
		|| c == '\v' || c == '\r')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	i = 0;
	while (iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num = num * sign;
	return (num);
}

/* int main ()
{

	char *test = "   		+-543123";
	printf("%d",ft_atoi(test));

	return 0;
}
*/
