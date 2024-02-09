/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/09 15:28:54 by asfletch         ###   ########.fr       */
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

void	parse_double_quote(t_mini *mini, int *j, int *i)
{
	char	*quoted_str;
	// char	*temp1 = NULL;
	// char	*temp2 = NULL;

	quoted_str = NULL;
	(*i)++;
	while (mini->prompt[*i] != '\"' && mini->prompt[*i] != '\0')
	{
		quoted_str = ft_char_join(quoted_str, mini->prompt[*i]);
		(*i)++;
	}
	mini->commands[0].cmd_args[*j] = ft_strdup(quoted_str);
	(*j)++;
	if (quoted_str)
	{
		free (quoted_str);
		quoted_str = NULL;
	}
	if (mini->prompt[*i] == '\"')
		(*i)++;
}

void	parse_trial(t_mini *mini)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (mini->prompt[i])
	{
		if (mini->prompt[i] != ' ' && mini->prompt[i] != '\"')
			temp = ft_char_join(temp, mini->prompt[i]);
		else if (mini->prompt[i] == '\"')
			parse_double_quote(mini, &j, &i);
		else if (mini->prompt[i] == ' ')
			parse_space(mini, &temp, &j, &i);
		while (mini->prompt[i] == ' ' && mini->prompt[i + 1] == ' ' && mini->prompt[i])
			i++;
		i++;
	}
	if (temp)
	{
		if (temp[0] != '\0')
			mini->commands[0].cmd_args[j++] = ft_strdup(temp);
		free(temp);
	}
}

void	parse_init(t_mini *mini)
{
	char **argv = NULL;
	int	nbr = 0;

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');
	mini->argv = argv;
	mini->commands = ft_calloc(1, sizeof(t_commands));
	mini->commands[0].cmd_args = ft_calloc(1 ,sizeof(char *) * 50);
	parse_trial(mini);
	int		i = 0;
	while (mini->commands[0].cmd_args[i])
	{
		printf("%s\n", mini->commands[0].cmd_args[i++]);
		nbr++;
	}
	printf("%d\n", nbr);
	if (is_built_in(mini) == 0)
	{
		pipex_main(argv, mini->env);
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

// void	parse_trial(t_mini *mini)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	i = 0;
// 	j = 0;
// 	temp = NULL;
// 	mini->commands = ft_calloc(1, sizeof(t_commands));
// 	while (mini->prompt[i])
// 	{
// 		temp = ft_char_join(temp, mini->prompt[i]);
// 		if (mini->prompt[i] == ' ')
// 		{
// 			parse_space(mini, &temp, j);
// 			j++;
// 			while (mini->prompt[i] == ' ' && mini->prompt[i + 1] == ' ')
// 				i++;
// 		}
// 		i++;
// 	}
// 	if (temp && temp[0] != '\0')
// 		parse_space(mini, &temp, j);
// 	if (temp)
// 		free(temp);
// }

// void	parse_trial(t_mini *mini)
// {
// 	int		i;
// 	int		j;
// 	int		len;
// 	char	*temp;
// 	char 	*prompt;

// 	prompt = mini->prompt;
// 	i = 0;
// 	temp = NULL;
// 	mini->commands = ft_calloc(1, sizeof(t_commands) * 1);
// 	j = 0;
// 	while (prompt[i])
// 	{
// 		temp = ft_char_join(temp, prompt[i]);
// 		if (prompt[i] == ' ')
// 		{
// 			parse_space(&mini, &i, &temp);
// 			len = ft_strlen(temp);
// 			printf("%d\n", len);
// 			mini->commands[j].cmd_args = malloc(sizeof(char *) * (len + 1));
// 			mini->commands[j].cmd_args[j] = ft_strdup(temp);
// 			free (temp);
// 			temp = NULL;
// 			printf("%s\n", mini->commands[j].cmd_args[j]);
// 			j++;
// 			while (prompt[i] == ' ' && prompt[i + 1] == ' ')
// 				i++;
// 		}
// 		if (prompt[i] == '\"')
// 		{
// 			i++;
// 			while (prompt[i] != '\"' && prompt[i])
// 			{
// 				temp = ft_char_join(temp, prompt[i]);
// 				i++;
// 			}
// 			if (prompt[i] == '\0')
// 			{
// 				while (1)
// 				{
// 					char *temp1 = readline("dquote> ");
// 					//append promt with
// 					char *temp2 = ft_strjoin(temp2 ,temp1);
// 					if (ft_strchr(temp2, '\"'))
// 					{
// 						temp = ft_strjoin(temp ,temp2);
// 						free (temp2);
// 						break ;
// 					}
// 					free(temp1);
// 				}
// 			}
// 			// ft_strcoopy..
// 		}
// 		if (prompt[i] == '\'')
// 		{
// 			i++;
// 			while (prompt[i] != '\'')
// 			{
// 				//store ar// temp char + char
// 				i++;
// 			}
// 			if (prompt[i] == '\0')
// 				while (1)
// 				{
// 					char *temp = readline("dquote> ");
// 					//append promt with

// 					if (ft_strchr(temp, '\''))
// 						break ;
// 					free(temp);
// 				}
// 		}
// 		if (prompt[i] == '|')
// 		{
// 			// add to node
// 		}
// 		i++;
// 	}
// }
