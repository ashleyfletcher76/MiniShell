/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:01:34 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/16 16:40:05 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/wait.h>

typedef struct s_here_doc
{
	char		*input;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_commands
{
	char				**cmd_args;
	char				*input;
	char				*output;
	int					indicator_input;
	int					indicator_output;
	struct s_commands	*next;
}	t_commands;

typedef struct s_pipex
{
	pid_t		*pids;
	int			**pipel;
	int			nbr_cmd;
	int			nbr_cmd_builts;
	char		**all_paths;
	char		**env;
	int			fd_in_orj;
	int			fd_out_orj;
	t_commands	*commands;
}	t_pipex;

typedef struct s_mini
{
	char		*prompt_msg;
	char		*prompt;
	char		*cwd;
	char		**argv;
	char		**env;
	t_commands	*commands;
}	t_mini;


#endif
