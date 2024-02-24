/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:06:50 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/24 17:49:02 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	direction_handler(t_pipex *pipex)
{
	int	i;
	int	direction_count;
	int	input;
	int	output;

	input = 0;
	output = 0;
	i = 1;
	direction_count = pipex->commands->input_index + pipex->commands->output_index;
	while (i <= direction_count + 1 && direction_count != 0)
	{
		if (i == pipex->commands->order_input[input])
		{
			input_handler(pipex, input);
			input++;
		}
		if (i == pipex->commands->order_output[output])
		{
			output_handler(pipex, output);
			output++;
		}
		i++;
	}
}

void	input_handler(t_pipex *pipex, int input)
{
	int		fd;
	char	*s;
	int		flag;

	flag = pipex->commands->indicator_input[input];
	s = pipex->commands->input[input];
	fd = 0;
	if (flag == TRUE)
		return (heredoc_found(pipex, input));
	fd = input_opener(pipex, s);
	input_dup2(fd, pipex);
	close(fd);
}

void	output_handler(t_pipex *pipex, int output)
{
	int		fd;
	char	*s;

	s = pipex->commands->output[output];
	fd = 0;
	if (pipex->commands->indicator_output[output] == FALSE)
		fd = output_opener(pipex, s);
	else
		fd = output_append_opener(pipex, s);

	output_dup2(fd, pipex);
	close(fd);
}

void	heredoc_found(t_pipex *pipex, int input)
{
	int	fd;

	fd = output_opener(pipex, "./.heredoc_found");
	output_dup2(fd, pipex);
	ft_printf("%s", pipex->commands->input[input]);
	close(fd);
	output_dup2(pipex->fd_out_orj, pipex);
	fd = input_opener(pipex, "./.heredoc_found");
	input_dup2(fd, pipex);
	close(fd);
	if (unlink("./.heredoc_found") == -1)
	{
		perror("unlink");
		exit(EXIT_FAILURE);
	}
}
