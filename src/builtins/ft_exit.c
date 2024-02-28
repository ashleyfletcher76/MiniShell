/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:08:04 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 13:22:05 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_long_long_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	num;

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

void	ft_exit(char **commands, t_pipex *pipex)
{
	// long long	num;

	cleaner (pipex);
	rl_clear_history();
	free_double_array(pipex->env);
	ft_printf("exit\n");
	if (commands[1] == NULL)
		exit(EXIT_SUCCESS);
	// if (commands[2] != NULL)
	// {
	// 	ft_putendl_fd("minishell: exit: too many arguments", 2);
	// 	pipex->exitcode = 1;
	// 	return ;
	// }
	// num = ft_exit_helper(commands[1]);
	// if (num == FALSE)
	// 	exit(255);
	exit(25);
}

int	ft_exit_helper(char *code)
{
	int			i;
	long long	num;

	num = ft_long_long_atoi(code);
	i = 0;
	if (LLONG_MAX <= num || num <= LLONG_MIN)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		return (FALSE);
	}
	while (code[i] == ' ' && code[i])
		i++;
	if (code[i] == '-' || code[i] == '+')
		i++;
	while (code[i])
	{
		if (!(code[i] >= '0' && code[i] <= '9'))
		{
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			return (FALSE);
		}
		i++;
	}
	return (num);
}
