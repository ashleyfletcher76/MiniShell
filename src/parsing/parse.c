/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:57:35 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/01 12:28:26 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_cmd(char **temp, int *j, t_commands **cmd, int indicator)
{
	t_commands	*new_node;

	if (*temp)
	{
		(*cmd)->cmd_args = ft_realloc_char((*cmd)->cmd_args, *j);
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

void	add_cmd_args(t_commands *cmd, char **temp, int *j)
{
	if (temp)
	{
		cmd->cmd_args = ft_realloc_char(cmd->cmd_args, *j);
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
			finalize_cmd(&temp, &j, &command, 0);
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
		finalize_cmd(&temp, &j, &command, 1);
}

void	parse_init(t_mini *mini)
{
	t_commands	*command;

	if (check_syntax(mini) == FALSE)
		return ;
	command = lstnew();
	parse_distributor(mini, command, 0, 0);
	exec_init(mini);
}

//print_commands(mini);
