/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_ft_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:01:53 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/11 14:38:30 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getenv("PWD");
	ft_putendl_fd(pwd,1);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i++]);
	}
}

void	ft_echo(char **commands)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (ft_strncmp(commands[1], "-n", 3) == 0)
	{
		i++;
		n = 1;
	}
	while (commands[i])
		ft_printf("%s ", commands[i++]);
	if (n == 0)
		ft_printf("\n");
}
