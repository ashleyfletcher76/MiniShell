/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:30:42 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/26 19:16:08 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(t_mini *mini)
{
	if (check_pipe(mini->prompt) == FALSE)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		mini->exitcode = 258;
		return (FALSE);
	}
	if (check_input_direction(mini->prompt) == FALSE || check_output_direction(mini->prompt) == FALSE)
	{
		mini->exitcode = 258;
		return (FALSE);
	}
	return (TRUE);
}

int	check_input_direction(char *s)
{
	int	i;

	i = 0;
	while ((s[i] == '\t' || s[i] == ' ') && s[i] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] == '<')
		{
			i++;
			if (s[i] == '<')
				i++;
			while ((s[i] == '\t' || s[i] == ' ') && (s[i] != '\0'))
				i++;
			if (s[i] == '\0')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2), FALSE);
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2), FALSE);
		}
		i = skip_quotes(s, i);
		i++;
	}
	return (TRUE);
}

int	check_output_direction(char *s)
{
	int	i;

	i = 0;
	while ((s[i] == '\t' || s[i] == ' ') && s[i] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] == '>')
		{
			i++;
			if (s[i] == '>')
				i++;
			while ((s[i] == '\t' || s[i] == ' ') && (s[i] != '\0'))
				i++;
			if (s[i] == '\0')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `newline'", 2), FALSE);
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				return (ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2), FALSE);
		}
		i = skip_quotes(s, i);
		i++;
	}
	return (TRUE);
}

int	check_pipe(char *s)
{
	int	i;

	i = 0;
	while ((s[i] == '\t' || s[i] == ' ') && s[i] != '\0')
		i++;
	if (s[i] == '|')
		return (FALSE);
	while (s[i])
	{
		if (s[i] == '|')
		{
			i++;
			while ((s[i] == '\t' || s[i] == ' ') && (s[i] != '\0' || s[i] != '|'))
				i++;
			if (s[i] == '|')
				return (FALSE);
		}
		i = skip_quotes(s, i);
		i++;

	}
	return (TRUE);
}

int	skip_quotes(char *s, int i)
{
	if (s[i] == '\"')
	{
		i++;
		while (s[i] != '\"' && s[i + 1] != '\0')
			i++;
	}
	if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i + 1] != '\0')
			i++;
	}
	return (i);
}
