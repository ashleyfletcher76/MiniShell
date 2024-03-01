/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:39:53 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 12:28:43 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error_message(t_mini *mini, char *cmds, int flag)
{
	if (flag == 0)
		ft_put3endl_fd("minishell: export: `", cmds,
			"': not a valid identifier", 2);
	else if (flag == 1)
		ft_put3endl_fd("minishell: unset: `",
			cmds, "': not a valid identifier", 2);
	mini->exitcode = 1;
}

// void	print_commands(t_mini *mini)
// {
// 	t_commands	*current = mini->commands;
// 	int			cmd_number = 1;
// 	int			j = 0;

// 	while (current != NULL)
// 	{
// 		printf("Command %d:\n", cmd_number++);
// 		if (current->cmd_args != NULL)
// 		{
// 			for	(int i = 0; current->cmd_args[i] != NULL; i++)
// 			{
// 				printf("  arg[%d]: %s\n", i, current->cmd_args[i]);
// 			}
// 		}
// 		if (current->input != NULL)
// 		{
// 			while (current->input[j])
// 			{
// 				printf("input = %s\n", current->input[j]);
// 				printf("input indicator = %d\n", current->indicator_input[j]);
// 				printf("order_idnex == %d\n", current->order_input[j]);
// 				j++;
// 			}
// 		}
// 		j = 0;
// 		if (current->output != NULL)
// 		{
// 			while (current->output[j])
// 			{
// 				printf("output = %s\n", current->output[j]);
// 				printf("output indicator = %d\n", current->indicator_output[j]);
// 				printf("order_idnex == %d\n", current->order_output[j]);
// 				j++;
// 			}
// 		}
// 		//printf("exit code = %d\n", mini->exitcode);
// 		current = current->next;
// 	}
// 	printf("-----------------------------\n");
// }
