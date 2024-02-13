/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:01:34 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/13 15:56:29 by asfletch         ###   ########.fr       */
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
