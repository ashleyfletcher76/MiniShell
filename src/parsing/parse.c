/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:08:04 by asfletch          #+#    #+#             */
/*   Updated: 2024/02/10 11:20:28 by asfletch         ###   ########.fr       */
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

void	parse_distributor(t_mini *mini)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	temp = NULL;
	while (mini->prompt[i])
	{
		if (mini->prompt[i] != ' ' && mini->prompt[i] != '\"' && mini->prompt[i] != '\'')
			temp = ft_char_join(temp, mini->prompt[i]);
		else if (mini->prompt[i] == '\"')
			parse_double_quote(mini, &j, &i);
		else if (mini->prompt[i] == '\'')
			parse_single_quote(mini, &i, &j);
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

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');
	mini->argv = argv;
	mini->commands = ft_calloc(1, sizeof(t_commands));
	mini->commands[0].cmd_args = ft_calloc(1 ,sizeof(char *) * 50);
	parse_distributor(mini);
	int	nbr = 0;
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

