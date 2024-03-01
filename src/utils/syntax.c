/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:30:42 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 13:40:00 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(int flag)
{
	if (flag == 0)
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
	else if (flag == 1)
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
	else if (flag == 2)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
	else if (flag == 3)
		ft_putendl_fd(
			"minishell: syntax error near unexpected token `newline'", 2);
	else if (flag == 4)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
}

int	check_syntax(t_mini *mini)
{
	if (check_pipe(mini->prompt) == FALSE)
	{
		free(mini->prompt);
		free(mini->prompt_msg);
		error_message(0);
		mini->exitcode = 258;
		return (FALSE);
	}
	if (check_input_direction(mini->prompt) == FALSE
		|| check_output_direction(mini->prompt) == FALSE)
	{
		free(mini->prompt);
		free(mini->prompt_msg);
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
				return (error_message(1), FALSE);
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				return (error_message(2), FALSE);
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
				return (error_message(3), FALSE);
			if (s[i] == '<' || s[i] == '>' || s[i] == '|')
				return (error_message(4), FALSE);
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
			while ((s[i] == '\t' || s[i] == ' ') && (s[i] != '\0'
					|| s[i] != '|'))
				i++;
			if (s[i] == '|')
				return (FALSE);
		}
		i = skip_quotes(s, i);
		i++;
	}
	return (TRUE);
}
