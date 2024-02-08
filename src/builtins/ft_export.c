/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:57:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/07 17:49:38 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export(char **commands, char **env)
{
	int i;
	int	equl_cnt;

	i = 0;
	if (commands[1] == NULL)
	{
		while (env[i])
			ft_printf("%s\n", env[i++]);
		return ;
	}
	equl_cnt = ft_count_equal(commands[1]);
	printf("%d\n", equl_cnt);
	if (equl_cnt == 0)
	{
		env[i] = env[i - 1];
		env[i - 1] = ft_strjoin(commands[1], "=");
		env[i + 1] = NULL;
	}
	while(env[i] != NULL)
	{
		if (ft_strncmp(env[i], commands[1], equl_cnt) == 0)
		{
			ft_strcpy(env[i], commands[1]);
			return ;
		}
		i++;
	}
	env[i] = env[i - 1];
	env[i - 1] = commands[1];
	env[i + 1] = NULL; 
}


int	ft_count_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}
