/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:29:17 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/13 16:43:57 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	ft_put3endl_fd(char *s, char *s1, char *s2, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, s1, ft_strlen(s1));
	write(fd, s2, ft_strlen(s2));
	write(fd, "\n", 1);
}
