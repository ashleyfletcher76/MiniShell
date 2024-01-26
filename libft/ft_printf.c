/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:39:27 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/06 11:46:36 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle(va_list args, const char c)
{
	if (c == 'i')
		return (nbrprinter(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_fd_print(va_arg(args, char *), 1));
	else if (c == 'c')
		return (ft_putchar_fd_print(va_arg(args, int), 1));
	else if (c == 'd')
		return (nbrprinter(va_arg(args, int)));
	else if (c == 'u')
		return (ft_unsignednbr_fd(va_arg(args, unsigned int)));
	else if (c == 'p')
		return (ft_pointerprint(va_arg(args, unsigned long long)));
	else if (c == 'x')
		return (hexatransformlower(va_arg(args, unsigned int)));
	else if (c == 'X')
		return (hexatransformupper(va_arg(args, unsigned int)));
	else if (c == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		count[2];

	count[1] = 0;
	i = -1;
	va_start(args, format);
	while (++i < ft_strlen_print(format))
	{
		if (format[i] == '%')
		{
			count[0] = handle(args, format[++i]);
			if (count[0] == -1)
				return (-1);
			count[1] += count[0];
		}
		else
		{
			if (write(1, &format[i], 1) == -1)
				return (-1);
			count[1]++;
		}
	}
	va_end(args);
	return (count[1]);
}

/* int main()
{
    int x;

	int result;
    result = printf("\001\002\007\v\010\f\r\n");
	ft_printf("\n%d",result);

	
   return (0);
} */