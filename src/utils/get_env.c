/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:57:07 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 18:38:32 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char **env, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
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

char	**dup_env(char **env)
{
	char	**dup;
	int		size;
	int		i;

	i = 0;
	size = array_size(env);
	dup = malloc(sizeof(char *) * (size + 1));
	while (env[i])
	{
		dup[i] = ft_strdup(env[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char	**dup_export(char **env)
{
	char	**export;
	int		i;
	char	*temp;

	i = -1;
	export = malloc (sizeof(char *) * (array_size(env) + 1));
	while (env[++i] != NULL)
		export[i] = ft_strdup(env[i]);
	export[i] = NULL;
	bouble_sort_char(export);
	export[i] = NULL;
	i = -1;
	while (export[++i])
	{
		temp = export_style(export[i]);
		export[i] = temp;
	}
	export[i] = NULL;
	return (export);
}

void	bouble_sort_char(char **export)
{
	int		i;
	int		sorted;
	char	*temp;

	temp = NULL;
	sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (export[i + 1] != NULL)
		{
			if (ft_strcmp(export[i], export[i + 1]) > 0)
			{
				temp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
}
