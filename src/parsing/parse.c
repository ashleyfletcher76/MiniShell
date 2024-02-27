/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/02/27 14:24:38 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	finalize_command(char **temp, int *j, t_commands **cmd, int indicator)
{
	t_commands	*new_node;

	if (*temp)
	{
		(*cmd)->cmd_args = ft_realloc_double_char((*cmd)->cmd_args, *j);
		if (*temp[0] != '\0' && *temp)
			(*cmd)->cmd_args[*j] = ft_strdup(*temp);
		else
			(*cmd)->cmd_args[*j] = ft_strdup("");
		(*j)++;
		free (*temp);
		*temp = NULL;
		(*cmd)->cmd_args[*j] = NULL;
	}
	if (indicator == 0)
	{
		new_node = lstnew();
		lstadd_back(cmd, new_node);
		(*cmd) = (*cmd)->next;
		*j = 0;
	}
}

void	add_cmd_args(t_commands *cmd, char **temp,int *j)
{
	if (temp)
	{
		cmd->cmd_args = ft_realloc_double_char(cmd->cmd_args, *j);
		cmd->cmd_args[(*j)++] = ft_strdup(*temp);
		cmd->cmd_args[*j] = NULL;
	}
}

char	*check_other_cmds(t_mini *mini, t_commands *cmd, char *temp, int *i)
{
	if (mini->prompt[*i] == '<')
			parse_input(mini, i, &cmd);
	else if (mini->prompt[*i] == '>')
			parse_output(mini, i, &cmd);
	else if (mini->prompt[*i] == '\'')
		temp = ft_strjoin_freeself(temp, parse_single_quote(mini, i));
	else if (mini->prompt[*i] == '\"')
		temp = ft_strjoin_freeself(temp, parse_double_quote(mini, i));
	else if (mini->prompt[*i] == '$')
		temp = ft_strjoin_freeself(temp, handle_dollar(mini, i));
	else if (mini->prompt[*i] != ' ' && mini->prompt[*i] != '\t')
		temp = ft_char_join(temp, mini->prompt[*i]);
	if (mini->prompt[*i] != '\0')
		(*i)++;
	return (temp);
}

void	parse_distributor(t_mini *mini, t_commands *command, int i, int j)
{
	char		*temp;

	temp = NULL;
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
				add_cmd_args(command, &temp, &j);
			free (temp);
			temp = NULL;
		}
		temp = check_other_cmds(mini, command, temp, &i);
	}
	if (temp)
		finalize_command(&temp, &j, &command, 1);
}

void	parse_init(t_mini *mini)
{
	t_commands	*command;

	if (check_syntax(mini) == FALSE)
		return ;
	command = lstnew();
	parse_distributor(mini, command, 0, 0);
	//print_commands(mini);
	exec_init(mini);
}

void	print_commands(t_mini *mini)
{
	t_commands	*current = mini->commands;
	int			cmd_number = 1;
	int			j = 0;

	while (current != NULL)
	{
		printf("Command %d:\n", cmd_number++);
		if (current->cmd_args != NULL)
		{
			for	(int i = 0; current->cmd_args[i] != NULL; i++)
			{
				printf("  arg[%d]: %s\n", i, current->cmd_args[i]);
			}
		}
		if (current->input != NULL)
		{
			while (current->input[j])
			{
				printf("input = %s\n", current->input[j]);
				printf("input indicator = %d\n", current->indicator_input[j]);
				printf("order_idnex == %d\n", current->order_input[j]);
				j++;
			}
		}
		j = 0;
		if (current->output != NULL)
		{
			while (current->output[j])
			{
				printf("output = %s\n", current->output[j]);
				printf("output indicator = %d\n", current->indicator_output[j]);
				printf("order_idnex == %d\n", current->order_output[j]);
				j++;
			}
		}
		//printf("exit code = %d\n", mini->exitcode);
		current = current->next;
	}
	printf("-----------------------------\n");
}
