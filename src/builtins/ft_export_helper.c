/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:18:30 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 19:37:56 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(1, export[i], ft_count_equal(export[i]));
		ft_printf("\"");
		ft_printf("%s", ft_strchr(export[i], '=') + 1);
		ft_printf("\"\n");
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

void	export_error_message(t_pipex *pipex, char **cmds, int flag)
{
	if (flag == 0)
		ft_put3endl_fd("minishell: export: `", cmds[1],
			"': not a valid identifier", 2);
	else if (flag == 1)
		ft_put3endl_fd("minishell: unset: `",
			cmds[1], "': not a valid identifier", 2);
	pipex->exitcode = 1;
}

int	check_variable(char *s)
{
	int	i;

	i = 0;
	if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		&& s[i] != '_')
		return (FALSE);
	while (s[i] != '=' && s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (2);
		if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
				|| (s[i] >= '0' && s[i] <= '9') || s[i] == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}
