#ifndef MINISHELL
#define MINISHELL

# include "structs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>

//main nessecaries
void		get_adresses(t_pipex *pipex);
char		*giveme_path(char *command, t_pipex *pipex);
char		*get_a_path(char *command, t_pipex *pipex);

//free stuff
void		free_struct(t_pipex *pipex);
void		free_double_int(int **array);
void		free_double_array(char **array);
void		free_tripple_array(char ***array);
void		waiter(t_pipex *pipex);

//erorror
void		error_handler(char *msg, t_pipex *pipex, int exitcode);

//piper.c
void		pipe_all(t_pipex *pipex);
void		pipe_close(t_pipex *pipex);
void		only_child(t_pipex *pipex, int i);
void		first_son(t_pipex *pipex, int i);
void		last_son(t_pipex *pipex, int i);
void		daughters(t_pipex *pipex, int i);
void		dup2er(int input, int output, t_pipex *pipex);
int			opener(t_pipex *pipex, int m);
void		piper(t_pipex *pipex);
void		forker(t_pipex *pipex, int i);

//utils
void		freearr(char **arr);
char		*give_me_prompt(t_mini *mini);
int			array_size(char **s);
int			commands_size_all(t_commands *lst);
int			commands_size_buildin(t_commands *lst);

//parsing
void		parse_init(t_mini *mini);
void		parse_distributor(t_mini *mini);
void		finalize_command(char **temp, int *j, t_commands **cmd, int indicator);
void		print_commands(t_mini *mini);

void		parse_space(t_mini *mini, char **temp, int *j, int *i, t_commands **cmd);
void		parse_double_quote(t_mini *mini, int *j, int *i, t_commands **cmd);
char		*dquote_helper(char *quoted_str);
void		parse_single_quote(t_mini *mini, int *j, int *i, t_commands **cmd);
char		*quote_helper(char *quoted_str);
void		parse_input(t_mini *mini, int *i, t_commands **cmd);
char		*append_heredoc(char *temp);
char		*full_heredoc(char *orig_str, char *new_str, char *new_line, int first_line);
void		parse_output(t_mini *mini, int *i, t_commands **cmd);
void		update_input_arg(t_commands **cmd, char **temp, int flag);
void		update_output_arg(t_commands **cmd, char **temp, int flag);

void		lstadd_back(t_commands **lst, t_commands *new_node);
t_commands	*lstnew(void);
t_commands	*lstlast(t_commands *lst);

char		*ft_char_join(char *s1, char c);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		*ft_strndup(const char *s1, size_t nbr);

//builtin
int			is_built_in(t_pipex *pipex);
int			which_build(char **commands, char **env);
int			exist_build(char **commands);
int			checkPathExistence(const char *path);
void		update_pwd_env(char **environ);
void		ft_cd(char **command, char **env);
void		ft_exit(char **commands);
void		ft_export(char **commands, char **env);
int			ft_export_error(char **commands, char **env);
int			ft_export_error_helper(char **commands, char **env);
int			ft_count_equal(char *s);
void		ft_export_helper(char **commands, char **env, int equl_cnt);
void		ft_export_print(char **env);
int			ft_export_command_check(char *s);
void		bouble_sort_char(char **export);
void		ft_unset(char **commands, char **env);
void		ft_pwd(void);
void		ft_env(char **env);
void		ft_echo(char **commands);

//exec
void		exec_init(t_mini *mini);
void		exec_main(t_mini *mini);
int			promt_help(t_mini *mini, char *user);
void		direction_handler(t_pipex *pipex);
void		input_handler(t_pipex *pipex);
void		output_handler(t_pipex *pipex);
void		output_handler_append(t_pipex *pipex);
void		heredoc_found(t_pipex *pipex);

#endif
