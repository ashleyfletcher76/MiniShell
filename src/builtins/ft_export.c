/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 10:57:10 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/10 14:44:38 by muhakose         ###   ########.fr       */
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
		ft_export_print(env);
		return ;
	}
	if (ft_export_command_check(commands[1]) == FALSE)
		return (ft_put3endl_fd("export", ": not valid in this context: ", commands[1], 2));
	else if (ft_export_command_check(commands[1]) == 2)
		return (ft_put3endl_fd("export", ": not an identifier: ", commands[1], 2));
	equl_cnt = ft_count_equal(commands[1]);
	while(env[i] != NULL && equl_cnt != 0)
	{
		if (ft_strncmp(env[i], commands[1], equl_cnt) == 0)
		{
			ft_strcpy(env[i], commands[1]);
			return ;
		}
		i++;
	}
	ft_export_helper(commands, env, equl_cnt);
}

void	ft_export_print(char **env)
{
	char	**export;
	char	*temp = NULL;
	int		i;

	i = 0;
	export = malloc (sizeof(char *) * (40));
	while (env[i] != NULL)
	{
		export[i] = ft_strdup(env[i]);
		i++;
	}
	export[i] = NULL;
	int sorted = 0;
	while (!sorted)
	{
		i = 0;
		sorted = 1;
		while (export[i + 1] != NULL)
		{
			if (strcmp(export[i], export[i + 1]) > 0)
			{
				temp = export[i];
				export[i] = export[i + 1];
				export[i + 1] = temp;
				sorted = 0;
			}
			i++;
		}
	}
	i = -1;
	while (export[++i])
		ft_printf("%s\n", export[i]);
	free_double_array(export);
}

void	ft_export_helper(char **commands, char **env, int equl_cnt)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	if (equl_cnt == 0)
	{
		env[i] = env[i - 1];
		env[i - 1] = ft_strjoin(commands[1], "=");
		env[i + 1] = NULL;
	}
	else
	{
		env[i] = env[i - 1];
		env[i - 1] = commands[1];
		env[i + 1] = NULL; 
	}
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

int	ft_export_command_check(char *s)
{
	int	i;

	i = 0;
	if (s[i] >= '0' && s[i] <= '9')
		return (2);
	while (s[i])
	{
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == '_' || s[i] == '='))
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
