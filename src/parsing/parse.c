/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/11 11:47:30 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_space(t_mini *mini, char **temp, int *j, int *i)
{
	if (mini->prompt[*i] == '\"')
		return ;
	if (mini->prompt[*i] == ' ' || mini->prompt[*i + 1] == '\0')
	{
		mini->commands[0].cmd_args[*j] = ft_strdup(*temp);
		(*j)++;
		if (*temp)
		{
			free (*temp);
			*temp = NULL;
		}
	}
	while (mini->prompt[*i] == ' ' && mini->prompt[*i + 1] == ' ')
		(*i)++;
}

void	finalize_command(t_mini *mini, char **temp, int *j, t_commands **cmd)
{
	t_commands	*new_cmd;

	if (*temp && (*temp[0] != '\0'))
	{
		(*cmd)->cmd_args[*j] = ft_strdup(*temp);
		(*j)++;
		free (*temp);
		*temp = NULL;
	}
	(*cmd)->cmd_args[*j] = NULL;
	if (mini->prompt[*j] == '|')
	{
		new_cmd = ft_calloc(1, sizeof(t_commands));
		new_cmd->cmd_args = ft_calloc(1, sizeof(char *) * 50);
		*cmd = new_cmd;
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
	command = ft_calloc(1, sizeof(t_commands));
	command->cmd_args = ft_calloc(1, sizeof(char *) * 50);
	mini->commands = command;
	while (mini->prompt[i])
	{
		if (mini->prompt[i] == '|')
		{
			finalize_command(mini, &temp, &j, &command);
			i++;
		}
		else if (mini->prompt[i] == '\"')
			parse_double_quote(mini, &j, &i);
		else if (mini->prompt[i] == '\'')
			parse_single_quote(mini, &i, &j);
		else if (mini->prompt[i] == ' ')
			parse_space(mini, &temp, &j, &i);
		else
			temp = ft_char_join(temp, mini->prompt[i]);
		while (mini->prompt[i] == ' ' && mini->prompt[i + 1] == ' ' && mini->prompt[i])
			i++;
		i++;
	}
	if (temp && temp[0] != '\0')
		finalize_command(mini, &temp, &j, &command);
}

void	parse_init(t_mini *mini)
{
	char **argv = NULL;

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');
	mini->argv = argv;
	mini->commands = ft_calloc(1, sizeof(t_commands));
	//mini->commands[0].cmd_args = ft_calloc(1 ,sizeof(char *) * 50);
	parse_distributor(mini);
	// print_commands(mini);

	if (is_built_in(mini) == 0)
	{
		pipex_main(argv, mini->env);
	}
}

void	print_commands(t_mini *mini)
{
	t_commands	*current = mini->commands;
	int			cmd_number = 1;

	while (current != NULL)
	{
		printf("Command %d:\n", cmd_number++);
		for	(int i = 0; current->cmd_args[i] != NULL; i++)
			printf("  arg[%d]: %s\n", i, current->cmd_args[i]);
		current = current->next;
	}
}

// void	parse_space(t_mini *mini, char **temp, int *j, int *i)
// {
// 	if (mini->prompt[*i] == '\"')
// 		return ;
// 	if (mini->prompt[*i] == ' ' || mini->prompt[*i + 1] == '\0')
// 	{
// 		mini->commands[0].cmd_args[*j] = ft_strdup(*temp);
// 		(*j)++;
// 		if (*temp)
// 		{
// 			free (*temp);
// 			*temp = NULL;
// 		}
// 	}
// 	while (mini->prompt[*i] == ' ' && mini->prompt[*i + 1] == ' ')
// 		(*i)++;
// }

// void	parse_distributor(t_mini *mini)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	i = 0;
// 	j = 0;
// 	temp = NULL;
// 	while (mini->prompt[i])
// 	{
// 		if (mini->prompt[i] != ' ' && mini->prompt[i] != '\"' && mini->prompt[i] != '\'')
// 			temp = ft_char_join(temp, mini->prompt[i]);
// 		else if (mini->prompt[i] == '\"')
// 			parse_double_quote(mini, &j, &i);
// 		else if (mini->prompt[i] == '\'')
// 			parse_single_quote(mini, &i, &j);
// 		else if (mini->prompt[i] == ' ')
// 			parse_space(mini, &temp, &j, &i);
// 		while (mini->prompt[i] == ' ' && mini->prompt[i + 1] == ' ' && mini->prompt[i])
// 			i++;
// 		i++;
// 	}
// 	if (temp)
// 	{
// 		if (temp[0] != '\0')
// 			mini->commands[0].cmd_args[j++] = ft_strdup(temp);
// 		free(temp);
// 	}
// }

// void	parse_init(t_mini *mini)
// {
// 	char **argv = NULL;

// 	argv = ft_split(mini->prompt, '\"');
// 	argv = ft_split(mini->prompt, '|');
// 	mini->argv = argv;
// 	mini->commands = ft_calloc(1, sizeof(t_commands));
// 	mini->commands[0].cmd_args = ft_calloc(1 ,sizeof(char *) * 50);
// 	parse_distributor(mini);
// 	int	nbr = 0;
// 	int	i = 0;
// 	while (mini->commands[0].cmd_args[i])
// 	{
// 		printf("%s\n", mini->commands[0].cmd_args[i++]);
// 		nbr++;
// 	}
// 	printf("%d\n", nbr);
// 	if (is_built_in(mini) == 0)
// 	{
// 		pipex_main(argv, mini->env);
// 	}
// }

