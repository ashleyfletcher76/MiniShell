/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 11:20:47 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	direction_handler(t_mini *mini)
{
	int	i;
	int	dir_count;
	int	input;
	int	output;

	input = 0;
	output = 0;
	i = 1;
	dup_saver_input(mini);
	dup_saver_output(mini);
	dir_count = mini->commands->input_index + mini->commands->output_index;
	while (i <= dir_count + 1 && dir_count != 0)
	{
		if (mini->commands->input != NULL)
		{
			if (i == mini->commands->order_input[input])
				input_handler(mini, input++);
		}
		if (mini->commands->output != NULL)
		{
			if (i == mini->commands->order_output[output])
				output_handler(mini, output++);
		}
		i++;
	}
}

void	input_handler(t_mini *mini, int input)
{
	int		fd;
	char	*s;
	int		flag;

	flag = mini->commands->indicator_input[input];
	s = mini->commands->input[input];
	fd = 0;
	if (mini->nbr_cmd == 0 && flag == TRUE)
		return ;
	if (flag == TRUE)
		return (heredoc_found(mini, input));
	fd = input_opener(mini, s);
	input_dup2(fd, mini);
	close(fd);
}

void	output_handler(t_mini *mini, int output)
{
	int		fd;
	char	*s;

	s = mini->commands->output[output];
	fd = 0;
	if (mini->commands->indicator_output[output] == FALSE)
		fd = output_opener(mini, s);
	else
		fd = output_append_opener(mini, s);
	output_dup2(fd, mini);
	close(fd);
}

void	heredoc_found(t_mini *mini, int input)
{
	int	fd;

	fd = 0;
	fd = output_opener(mini, ".heredoc_found");
	output_dup2(fd, mini);
	ft_printf("%s", mini->commands->input[input]);
	close(fd);
	output_dup2(mini->fd_out_orj, mini);
	fd = input_opener(mini, ".heredoc_found");
	input_dup2(fd, mini);
	close(fd);
	if (unlink(".heredoc_found") == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}
}
