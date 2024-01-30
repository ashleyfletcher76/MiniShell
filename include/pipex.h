/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:01:34 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/30 16:22:21 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include "../libft/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	pid_t	*pids;
	int		**pipel;
	int		nbr_cmd;
	char	**all_paths;
	char	**command_paths;
	char	**special_paths;
	char	**env;
	char	**av;
	char	*input;
	char	*output;
}	t_pipex;

//main nessecaries
void	get_adresses(t_pipex *pipex);

char	*giveme_path(char *command, t_pipex *pipex);
char	*get_args(t_pipex *pipex, int i);
char	*get_a_path(char *command, t_pipex *pipex);

//free stuff
void	free_struct(t_pipex *pipex);
void	free_double_int(int **array);
void	free_double_array(char **array);
void	free_tripple_array(char ***array);
void	waiter(t_pipex *pipex);

//erorror
void	error_handler(char *msg, t_pipex *pipex, int exitcode);

//piper.c
void	pipe_all(t_pipex *pipex);
void	pipe_close(t_pipex *pipex);
void	only_child(t_pipex *pipex, int i);
void	first_son(t_pipex *pipex, int i);
void	last_son(t_pipex *pipex, int i);
void	daughters(t_pipex *pipex, int i);
void	dup2er(int input, int output, t_pipex *pipex);
int		opener(t_pipex *pipex, int m);
void	piper(t_pipex *pipex);
void	forker(t_pipex *pipex, int i);
void	pipex_main(char **av, char **env);

#endif
