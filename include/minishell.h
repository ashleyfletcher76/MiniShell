#ifndef MINISHELL
#define MINISHELL

#include "../libft/libft.h"
#include "pipex.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>


typedef struct s_commands
{
	char				**cmd_args;
	char				*input;
	char				*output;
	int					indicator;
	struct s_commands	 *next;
}	t_commands;

typedef struct s_mini
{
	char		*prompt_msg;
	char		*prompt;
	char		*cwd;
	char		**argv;
	char		**env;
	t_commands	*commands;
}	t_mini;


void	freearr(char **arr);
char	*give_me_prompt(t_mini *mini);
int		array_size(char **s);

void	parse_init(t_mini *mini);
void	parse_trial(t_mini *mini);

void	parse_space(t_mini *mini, char **temp, int *j, int *i);
void	parse_double_quote(t_mini *mini, int *j, int *i);

char	*ft_char_join(char *s1, char c);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
char	*ft_strndup(const char *s1, size_t nbr);

//builtin
int		is_built_in(t_mini *mini);
int		build_get_args(char *command, char **env);
int		which_build(char **commands, char **env);
int		checkPathExistence(const char *path);
void	update_pwd_env(char **environ);
void	ft_cd(char **command, char **env);
void	ft_exit(char **commands);
void	ft_export(char **commands, char **env);
int		ft_count_equal(char *s);

//exec
void	exec_init(t_mini *mini);
int		promt_help(t_mini *mini, char *user);


#endif
