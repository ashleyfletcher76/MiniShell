/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:14:59 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/26 12:53:11 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands	*lstnew(void)
{
	t_commands	*new;

	new = (t_commands *)malloc(sizeof(t_commands));
	if (new == NULL)
		return (NULL);
	new->cmd_args = ft_calloc(1, sizeof(char *) * 2);
	new->input = ft_calloc(1, sizeof(char *) * 50);
	new->output = ft_calloc(1, sizeof(char *) * 50);
	new->indicator_input = ft_calloc(1, sizeof(int *) * 50);
	new->indicator_output = ft_calloc(1, sizeof(int *) * 50);
	new->order_input = ft_calloc(1, sizeof(int *) * 50);
	new->order_output = ft_calloc(1, sizeof(int *) * 50);
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
