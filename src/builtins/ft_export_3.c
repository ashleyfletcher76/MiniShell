/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:08:16 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 18:42:39 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_style(char	*s)
{
	char	*temp;
	int		equal;

	equal = ft_count_equal(s);
	if (equal == 0)
		equal = ft_strlen(s);
	temp = ft_strjoin_freeself(ft_strdup("declare -x "), ft_strndup(s, equal));
	equal = ft_count_equal(s);
	if (equal != 0)
		temp = ft_char_join(temp, '\"');
	equal = ft_count_equal(s);
	if (equal != 0)
		temp = ft_strjoin_freeself(temp, ft_strdup(ft_strchr(s, '=') + 1));
	if (equal != 0)
		temp = ft_char_join(temp, '\"');
	free(s);
	return (temp);
}

char	*export_style_append(char	*s)
{
	char	*temp;

	temp = ft_strjoin_freeself(ft_strdup("declare -x "),
			ft_strndup(s, ft_count_equal(s)));
	temp = ft_char_join(temp, '\"');
	temp = ft_strjoin_freeself(temp, ft_strdup(ft_strchr(s, '=') + 1));
	temp = ft_char_join(temp, '\"');
	free(s);
	return (temp);
}

char	*export_style_append_2(char	*s, char *val)
{
	char	*temp;

	temp = ft_strndup(s, ft_strlen(s) - 1);
	temp = ft_strjoin_freeself(temp, val);
	temp = ft_char_join(temp, '\"');
	free(s);
	return (temp);
}

void	add_append_export(char *comds, t_mini *mini)
{
	char	*var;
	char	*val;
	int		equal;
	int		i;

	i = -1;
	equal = ft_count_equal(comds) - 2;
	if (equal == -2)
		return ;
	if (ft_strchr(comds, '=') != NULL)
		val = ft_strdup(ft_strchr(comds, '=') + 1);
	var = ft_strndup(comds, equal);
	while (mini->export[++i])
	{
		if (if_check(mini->export[i] + 11, var))
		{
			free(var);
			mini->export[i] = export_style_append_2(mini->export[i], val);
			return ;
		}
	}
	add_export_helper(comds, mini, var);
	return (free(val), free(var));
}

void	add_export(char *comds, t_mini *mini)
{
	size_t		equal;
	int			i;

	i = 0;
	equal = ft_count_equal(comds);
	if (equal == 0)
		equal = ft_strlen(comds);
	while (mini->export[i])
	{
		if (if_check(mini->export[i] + 11, comds))
		{
			if (equal == ft_strlen(comds))
				return ;
			free(mini->export[i]);
			mini->export[i] = export_style(ft_strdup(comds));
			return ;
		}
		i++;
	}
	add_export_helper(comds, mini, NULL);
}
