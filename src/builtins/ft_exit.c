/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/17 10:13:19 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char **commands)
{
	// cleanin and exit
	if (commands[1] != NULL)
		exit(ft_atoi(commands[1]));
	else
		exit(EXIT_SUCCESS);
}
