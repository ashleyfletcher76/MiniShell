/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:45:25 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/09 17:08:56 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_equal2(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (-1);
		i++;
	}
	return (i);
}

void	ft_unset(char **commands, char **env)
{
	int		i;
	//char	*temp;
	int		count_eql;

	//temp = NULL;
	i = 0;
	if (commands[1] == NULL)
		return (ft_putendl_fd("unset: not enough arguments", 2));
	count_eql = ft_count_equal2(commands[1]);
	if (count_eql == -1 )
		return (ft_put3endl_fd("unset: ", commands[1], ": invalid parameter name", 2));
	if (ft_export_command_check(commands[1]) == FALSE || ft_export_command_check(commands[1]) == 2)
		return (ft_put3endl_fd("unset: ", commands[1], ": invalid parameter name", 2));
	while (env[i])
	{
		if (ft_strncmp(env[i], commands[1], count_eql) == 0)
		{
			while (env[i])
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i - 1] = NULL;
			return ;
		}
		i++;
	}
}
