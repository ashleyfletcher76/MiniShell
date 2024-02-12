#ifndef MINISHELL
#define MINISHELL

#include "../libft/libft.h"
#include "pipex.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <signal.h>

typedef struct s_indexes
{
	int	prompt_index;
	int	args_index;
	int	input_index;
	int	output_index;
}	t_indexs;

typedef struct s_commands
{
	char				**cmd_args;
	char				*input;
	char				*double_input;
	char				*output;
	char				*double_output;
	int					indicator;
	struct s_commands	*next;
}	t_commands;

typedef struct s_mini
{
	char		*prompt_msg;
	char		*prompt;
	char		*cwd;
	char		**argv;
	char		**env;
	t_indexs	*indexes;
	t_commands	*commands;
}	t_mini;

void		freearr(char **arr);
char		*give_me_prompt(t_mini *mini);
int			array_size(char **s);

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
void		parse_output(t_mini *mini, int *i, t_commands **cmd);

void		lstadd_back(t_commands **lst, t_commands *new_node);
t_commands	*lstnew(void);
t_commands	*lstlast(t_commands *lst);

char		*ft_char_join(char *s1, char c);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char		*ft_strndup(const char *s1, size_t nbr);

//builtin
int			is_built_in(t_mini *mini);
int			build_get_args(char *command, char **env);
int			which_build(char **commands, char **env);
int			checkPathExistence(const char *path);
void		update_pwd_env(char **environ);
void		ft_cd(char **command, char **env);
void		ft_exit(char **commands);
void		ft_export(char **commands, char **env);
int			ft_count_equal(char *s);
void		ft_export_helper(char **commands, char **env, int equl_cnt);
void		ft_export_print(char **env);
int			ft_export_command_check(char *s);
void		ft_unset(char **commands, char **env);
void		ft_pwd(void);
void		ft_env(char **env);
void		ft_echo(char **commands);

//exec
void		exec_init(t_mini *mini);
int			promt_help(t_mini *mini, char *user);


#endif
