/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:01:34 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/12 14:00:01 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>

typedef struct s_commands
{
	char				**cmd_args;
	char				*input;
	char				*output;
	int					indicator;
	char				*double_input;
	char				*double_output;
	struct s_commands	*next;
}	t_commands;

typedef struct s_pipex
{
	pid_t		*pids;
	int			**pipel;
	int			nbr_cmd;
	char		**all_paths;
	char		**env;
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
