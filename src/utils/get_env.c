/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:57:07 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/23 15:53:40 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_env(char **env, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], var, len - 1) == 0)
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**update_env(char **env, char *var, char *value)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var - 1)) == 0)
		{
			temp = ft_strjoin(var, "=");
			env[i] = ft_strcat(temp, value);
			free(temp);
			return (env);
		}
		i++;
	}
	if (env[i] == NULL)
	{
		temp = ft_strjoin(var, "=");
		env[i] = ft_strcat(temp, value);
		env[i + 1] = NULL;
		free(temp);
		return (env);
	}
	return (env);
}
