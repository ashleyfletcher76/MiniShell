/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:14:59 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/13 12:33:17 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_commands	*lstnew(void)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (new == NULL)
		return (NULL);
	new->cmd_args = ft_calloc(1, sizeof(char *) * 50);
	new->input = NULL;
	new->output = NULL;
	new->indicator_input = 0;
	new->indicator_output = 0;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_commands **lst, t_commands *new_node)
{
	t_commands	*last;

	if (lst)
	{
		if (*lst)
		{
			last = lstlast(*lst);
			last->next = new_node;
		}
		else
			*lst = new_node;
	}
}

t_commands	*lstlast(t_commands *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
