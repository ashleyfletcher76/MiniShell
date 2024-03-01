/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:01:34 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 12:15:28 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/wait.h>

typedef struct s_commands
{
	char				**cmd_args;
	char				**input;
	char				**output;
	int					*indicator_input;
	int					*indicator_output;
	int					*order_input;
	int					*order_output;
	int					input_index;
	int					output_index;
	struct s_commands	*next;
}	t_commands;

typedef struct s_mini
{
	char		*prompt_msg;
	char		*prompt;
	char		*cwd;
	char		**env;
	char		**export;
	char		**all_paths;
	int			nbr_cmd;
	int			nbr_cmd_builts;
	int			fd_in_orj;
	int			fd_out_orj;
	int			**pipel;
	int			exitcode;
	int			expand_heredoc;
	pid_t		*pids;
	t_commands	*commands;
	t_commands	*temp_cmds;
}	t_mini;

#endif
