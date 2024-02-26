/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/26 12:23:21 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_command(char **temp, int *j, t_commands **cmd, int indicator)
{
	t_commands	*new_node;

	if (*temp)
	{
		if (*temp[0] != '\0' && *temp)
			(*cmd)->cmd_args[*j] = ft_strdup(*temp);
		else
			(*cmd)->cmd_args[*j] = ft_strdup("");
		(*j)++;
		free (*temp);
		*temp = NULL;
	}
	if (indicator == 0)
	{
		(*cmd)->cmd_args[*j] = NULL;
		new_node = lstnew();
		lstadd_back(cmd, new_node);
		(*cmd) = (*cmd)->next;
		*j = 0;
	}
}

void	parse_distributor(t_mini *mini)
{
	int			i;
	int			j;
	t_commands	*command;
	char		*temp;

	i = 0;
	j = 0;
	temp = NULL;
	//temp = ft_strdup("");
	command = lstnew();
	mini->commands = command;
	while (mini->prompt[i])
	{
		if (mini->prompt[i] == '|')
		{
			finalize_command(&temp, &j, &command, 0);
			i++;
		}
		else if (mini->prompt[i] == ' ' && mini->prompt[i + 1] != ' ')
		{
			if (temp)
				command->cmd_args[j++] = ft_strdup(temp);
			free(temp);
			temp = NULL;
		}
		if (mini->prompt[i] == '<')
			parse_input(mini, &i, &command);
		else if (mini->prompt[i] == '>')
			parse_output(mini, &i, &command);
		else if (mini->prompt[i] == '\'')
			temp = ft_strjoin_freeself(temp, parse_single_quote(mini, &i));
		else if (mini->prompt[i] == '\"')
			temp = ft_strjoin_freeself(temp, parse_double_quote(mini, &i));
		else if (mini->prompt[i] == '$')
			temp = ft_strjoin_freeself(temp, handle_dollar(mini, &i));
		else if (mini->prompt[i] != ' ' && mini->prompt[i] != '\t')
			temp = ft_char_join(temp, mini->prompt[i]);
		if (mini->prompt[i] != '\0')
			i++;
	}
	if (temp)
		finalize_command(&temp, &j, &command, 1);
}

void	parse_init(t_mini *mini)
{
	parse_distributor(mini);
}

void	print_commands(t_mini *mini)
{
	t_commands	*current = mini->commands;
	int			cmd_number = 1;
	int			j = 0;

	while (current != NULL)
	{
		printf("Command %d:\n", cmd_number++);
		for	(int i = 0; current->cmd_args[i] != NULL; i++)
		{
			printf("  arg[%d]: %s\n", i, current->cmd_args[i]);
		}
		while (current->input[j])
		{
			printf("input = %s\n", current->input[j]);
			printf("input indicator = %d\n", current->indicator_input[j]);
			printf("order_idnex == %d\n", current->order_input[j]);
			j++;
		}
		j = 0;
		while (current->output[j])
		{
			printf("output = %s\n", current->output[j]);
			printf("output indicator = %d\n", current->indicator_output[j]);
			printf("order_idnex == %d\n", current->order_output[j]);
			j++;
		}
		//printf("exit code = %d\n", mini->exitcode);
		current = current->next;
	}
	printf("-----------------------------\n");
}
