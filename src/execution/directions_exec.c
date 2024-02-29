/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/29 14:25:49 by asfletch         ###   ########.fr       */
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
	dir_count = mini->temp_cmds->input_index + mini->temp_cmds->output_index;
	while (i <= dir_count + 1 && dir_count != 0)
	{
		if (mini->temp_cmds->input != NULL)
		{
			if (i == mini->temp_cmds->order_input[input])
				input_handler(mini, input++);
		}
		if (mini->temp_cmds->output != NULL)
		{
			if (i == mini->temp_cmds->order_output[output])
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

	flag = mini->temp_cmds->indicator_input[input];
	s = mini->temp_cmds->input[input];
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

	s = mini->temp_cmds->output[output];
	fd = 0;
	if (mini->temp_cmds->indicator_output[output] == FALSE)
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
	ft_printf("%s", mini->temp_cmds->input[input]);
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
