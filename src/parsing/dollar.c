/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/17 12:35:27 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_dollar(t_mini *mini, int*i, int *j, t_commands **cmd)
{
	char	*new_temp;
	char	*exit_code;

	new_temp = NULL;
	if (mini->prompt[*i] == '$')
	{
		if (mini->prompt[*i + 1] == '?')
		{
			(*i)++;
			exit_code = ft_itoa(mini->exitcode);
			(*cmd)->cmd_args[*j] = exit_code;
			return ;
		}
		(*i)++;
		while (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\0')
		{
			new_temp = ft_char_join(new_temp, mini->prompt[*i]);
			(*i)++;
		}
	}
	new_temp = getenv(new_temp);
	(*cmd)->cmd_args[*j] = ft_strdup(new_temp);
	(*j)++;
}

// char	*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str)
// {

// }
