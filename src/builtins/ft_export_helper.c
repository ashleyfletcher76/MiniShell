/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:18:30 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/19 14:46:39 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_export_print(char **env)
{
	char	**export;
	int		i;

	i = 0;
	export = malloc (sizeof(char *) * (40));
	while (env[i] != NULL)
	{
		export[i] = ft_strdup(env[i]);
		i++;
	}
	export[i] = NULL;
	bouble_sort_char(export);
	i = -1;
	while (export[++i])
	{
		ft_printf("declare -x ");
		ft_printf("%s\n", export[i]);
	}
	free_double_array(export);
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

void	ft_export_helper(char **commands, char **env, int equl_cnt)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	if (equl_cnt != 0)
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
	int	count_eql;

	count_eql = ft_count_equal(s);
	i = 0;
	if ((s[i] >= '0' && s[i] <= '9') || s[i] == '=')
		return (2);
	while (s[i])
	{
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '-' || s[i] == '/' || s[i] == ':' || (s[i] >= '0' && s[i] <= '9') || s[i] == '_' || s[i] == '=' || s[i] == '$' || s[i] == ' '))
			return (FALSE);
		if ((count_eql == 0 && s[i] == '-') || (i < count_eql && s[i] == '-'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
