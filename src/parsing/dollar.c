/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 10:20:15 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/17 11:13:23 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_dollar(t_mini *mini, int*i, int *j, t_commands **cmd)
{
	char	*new_temp;

	new_temp = NULL;
	if (mini->prompt[*i] == '$')
	{
		if (mini->prompt[*i + 1] == '?')
		{
			mini->exitcode = ft_itoa(mini->exitcode);
			(*cmd)->cmd_args[*j] = mini->exitcode;
			break ;
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
