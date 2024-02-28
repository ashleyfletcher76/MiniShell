/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freearr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:00:46 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/28 14:05:41 by asfletch         ###   ########.fr       */
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

void	cleaner(t_pipex *pipex)
{
	commands_cleaner(pipex->mini->commands);
	free_struct(pipex);
	free (pipex->mini->cwd);
	free (pipex->mini->prompt);
	free (pipex->mini->prompt_msg);
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
		//free (head);
		head = next;
	}
}
