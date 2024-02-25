/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/25 09:54:57 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **commands)
{
	// cleanin and exit
	if (commands[2] != NULL)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		exit (EXIT_FAILURE);
	}
	if (commands[1] != NULL)
		ft_exit_helper(commands[1]);
	ft_printf("exit\n");
	exit(EXIT_SUCCESS);
}

void	ft_exit_helper(char *code)
{
	int	i;

	i = 0;
	while (code[i] == ' ' && code[i])
		i++;
	if (code[i] == '-' || code[i] == '+')
		i++;
	while(code[i])
	{
		if (!(code[i] >= '0' && code[i] <= '9'))
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit (255);
		}
		i++;
	}
	ft_printf("exit\n");
	exit(ft_atoi(code));
}
