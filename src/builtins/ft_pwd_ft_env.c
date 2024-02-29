/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_ft_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:01:53 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 11:27:24 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_putendl_fd(cwd, 1);
	mini->exitcode = 0;
}

void	ft_env(char **env, t_mini *mini)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i++]);
	}
	mini->exitcode = 0;
}

void	ft_echo(char **commands, t_mini *mini)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	while (ft_strncmp(commands[i], "-n", 3) == 0 && commands[i])
	{
		i++;
		n = 1;
	}
	while (commands[i] && commands[i + 1] != NULL)
		ft_printf("%s ", commands[i++]);
	if (commands[i])
		ft_printf("%s", commands[i]);
	if (n == 0)
		ft_printf("\n");
	mini->exitcode = 0;
}
