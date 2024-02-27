/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:27:17 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 13:37:02 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	commands_size_all(t_commands *lst)
{
	size_t	len;

	len = 0;
	if (lst->cmd_args == NULL || lst->cmd_args[0] == NULL)
		return (0);
	while (lst)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
}

int	commands_size_buildin(t_commands *lst)
{
	size_t	len;

	if (lst->cmd_args == NULL || lst->cmd_args[0] == NULL)
		return (0);
	len = 0;
	if (lst->cmd_args == NULL || lst->cmd_args[0] == NULL)
		return (0);
	while (lst)
	{
		if (exist_build(lst->cmd_args) == TRUE)
			len++;
		lst = lst -> next;
	}
	return (len);
}
