/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:14:59 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/27 12:00:24 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*lstnew(void)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (new == NULL)
		return (NULL);
	new->cmd_args = NULL;
	new->input = NULL;
	new->output = NULL;
	new->indicator_input = NULL;
	new->indicator_output = NULL;
	new->order_input = NULL;
	new->order_output = NULL;
	new->input_index = 0;
	new->output_index = 0;
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
