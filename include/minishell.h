#ifndef MINISHELL
#define MINISHELL

# define ANSI_COLOR_RESET	"\x1b[0m"

# include "structs.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <termios.h>
# include <limits.h>

volatile sig_atomic_t	sigint_received;

//main nessecaries
void		prompt_init(t_mini *mini, int exit_code);
int			main(int ac, char **av, char **env);

//free stuff
void		free_struct(t_pipex *pipex);
void		free_double_int(int **array);
void		free_double_array(char **array);
void		free_tripple_array(char ***array);
void		waiter(t_pipex *pipex);

//error
void		error_handler(char *msg, t_pipex *pipex, int exitcode);

//utils
void		freearr(char **arr);
char		*give_me_prompt(t_mini *mini);
int			array_size(char **s);
int			commands_size_all(t_commands *lst);
int			commands_size_buildin(t_commands *lst);
int			promt_help(t_mini *mini, char *user);
char		*get_env(char **env, char *var);
char		**update_env(char **env, char *var, char *value);
int			check_syntax(t_mini *mini);
int			check_pipe(char *s);
int			check_input_direction(char *s);
int			check_output_direction(char *s);
int			skip_quotes(char *s, int i);
int			skip_whitespace(char c);
int			no_whitespace_skip(char c);
int			*ft_realloc_int(int *ptr, int j);

//parsing
void		parse_init(t_mini *mini);
void		parse_distributor(t_mini *mini, t_commands *command, int i,  int j);
void		finalize_command(char **temp, int *j, t_commands **cmd, int indicator);
void		print_commands(t_mini *mini);
void		parse_space(t_mini *mini, char **temp, int *j, int *i, t_commands **cmd);
char		*parse_double_quote(t_mini *mini, int *i);
char		*dquote_helper(char *quoted_str);
char		*parse_single_quote(t_mini *mini, int *i);
char		*quote_helper(char *quoted_str);
void		parse_input(t_mini *mini, int *i, t_commands **cmd);
char		*append_heredoc(char *temp);
char		*full_heredoc(char *orig_str, char *new_str, char *new_line, int first_line);
void		parse_output(t_mini *mini, int *i, t_commands **cmd);
void		update_input_arg(t_commands **cmd, char **temp, int flag);
void		update_output_arg(t_commands **cmd, char **temp, int flag);
char		*handle_dollar(t_mini *mini, int *i);
char		*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str);

void		add_cmd_args(t_commands *cmd, char **temp,int *j);
char		*check_other_cmds(t_mini *mini, t_commands *cmd, char *temp, int *i);

void		lstadd_back(t_commands **lst, t_commands *new_node);
t_commands	*lstnew(void);
t_commands	*lstlast(t_commands *lst);

char		*ft_char_join(char *s1, char c);
void		*ft_realloc(void *ptr, int old_size, int new_size);
char		*ft_strndup(const char *s1, size_t nbr);
char		**ft_realloc_double_char(char **ptr, int j);
int			*ft_realloc_int(int *ptr, int j);

//builtin
int			is_built_in(t_pipex *pipex);
int			which_build(char **commands, char **env, t_pipex *pipex);
int			exist_build(char **commands);
int			checkPathExistence(const char *path);
void		update_pwd_env(t_pipex *pipex);
void		update_oldpwd_env(t_pipex *pipex, char *temp);
void		ft_cd(char **command, char **env, t_pipex *pipex);
void		ft_exit(char **commands, t_pipex *pipex);
int			ft_exit_helper(char *code);
void		ft_export(char **commands, char **env, t_pipex *pipex);
int			ft_export_error(char **commands, char **env);
int			ft_export_error_helper(char **commands, char **env);
int			ft_count_equal(char *s);
void		ft_export_helper(char **commands, char **env, int equl_cnt);
void		ft_export_print(char **env);
int			ft_export_command_check(char *s);
void		bouble_sort_char(char **export);
void		ft_unset(char **commands, char **env, t_pipex *pipex);
void		ft_pwd(t_pipex *pipex);
void		ft_env(char **env, t_pipex *pipex);
void		ft_echo(char **commands, t_pipex *pipex);

//exec
void		exec_init(t_mini *mini);
void		exec_main(t_mini *mini);
void		pipe_all(t_pipex *pipex);
void		pipe_close(t_pipex *pipex);
void		only_child(t_pipex *pipex, int i);
void		first_son(t_pipex *pipex, int i);
void		last_son(t_pipex *pipex, int i);
void		daughters(t_pipex *pipex, int i);
void		piper(t_pipex *pipex);
void		forker(t_pipex *pipex, int i);
void		get_adresses(t_pipex *pipex);
char		*giveme_path(char *command, t_pipex *pipex);
char		*get_a_path(char *command, t_pipex *pipex);
void		file_check(char *command, t_pipex *pipex);

//direction
void		direction_handler(t_pipex *pipex);
void		input_handler(t_pipex *pipex, int input);
void		output_handler(t_pipex *pipex, int output);
void		output_dup2(int input,t_pipex *pipex);
void		input_dup2(int input,t_pipex *pipex);
void		dup2er(int input, int output, t_pipex *pipex);
int			output_opener(t_pipex *pipex, char *s);
int			output_append_opener(t_pipex *pipex, char *s);
int			input_opener(t_pipex *pipex, char *s);
void		dup_saver(t_pipex *pipex, int flag);
void		heredoc_found(t_pipex *pipex, int input);

void		configure_terminal(void);
void		sigint_handler(int sig);
void		sig_init(void);

#endif
