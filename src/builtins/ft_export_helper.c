/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:18:30 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 12:25:31 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_export_error(t_mini *mini, char *commands)
{
	int	flag;

	flag = check_variable(commands);
	if (flag == FALSE)
	{
		export_error_message(mini, commands, 0);
	}
	return (flag);
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

void	add_export_helper(char *commands, t_mini *mini, char *var)
{
	int	i;

	i = 0;
	while (mini->export[i])
		i++;
	if (var != NULL && mini->export[i] == NULL)
	{
		mini->export = ft_realloc_char(mini->export, i);
		free(mini->export[i]);
		mini->export[i] = mini->export[i - 1];
		mini->export[i - 1] = export_style_append(ft_strjoin(var,
					ft_strchr(commands, '=')));
		mini->export[i + 1] = NULL;
	}
	if (var == NULL && mini->export[i] == NULL)
	{
		mini->export = ft_realloc_char(mini->export, i);
		free(mini->export[i]);
		mini->export[i] = mini->export[i - 1];
		mini->export[i - 1] = export_style(ft_strdup(commands));
		mini->export[i + 1] = NULL;
	}
}
