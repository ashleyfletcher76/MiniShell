/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:00:46 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 11:10:45 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freearr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		free(arr[i]);
		arr[i] = NULL;
	}
	free (arr);
}

void	all_cleaner(t_mini *mini)
{
	free_double_array(mini->env);
	free_double_array(mini->export);
	cleaner(mini);
	rl_clear_history();
}

void	cleaner(t_mini *mini)
{
	commands_cleaner(mini->commands);
	free_struct(mini);
	if (mini->prompt != NULL)
		free (mini->prompt);
	if (mini->prompt_msg != NULL)
		free (mini->prompt_msg);
}

void	commands_cleaner(t_commands *commds)
{
	t_commands	*head;
	t_commands	*next;

	head = commds;
	while (head)
	{
		free_double_array(head->cmd_args);
		free_double_array(head->input);
		free_double_array(head->output);
		if (head->indicator_input != NULL)
			free(head->indicator_input);
		if (head->indicator_output != NULL)
			free(head->indicator_output);
		if (head->order_input != NULL)
			free(head->order_input);
		if (head->order_output != NULL)
			free(head->order_output);
		next = head->next;
		if (head != NULL)
			free (head);
		head = next;
	}
}
