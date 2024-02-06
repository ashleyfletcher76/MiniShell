#ifndef MINISHELL
#define MINISHELL

#include "../libft/libft.h"
#include "pipex.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>


typedef struct s_commands
{
	char	*cmd;
	char	*cmd_args;
	char	**args;
}	t_commands;

typedef struct s_mini
{
	t_commands	*commands;
	char		*prompt_msg;
	char		*prompt;
	char		*cwd;
	char		**argv;
	char		**env;
}	t_mini;


void	freearr(char **arr);
char	*give_me_prompt(t_mini *mini);
int		array_size(char **s);

void	parse_init(t_mini *mini);


//builtin
int		is_built_in(t_mini *mini);
int		build_get_args(char *command, char **env);
int		which_build(char **commands, char **env);
int		checkPathExistence(const char *path);
void	update_pwd_env(char **environ);
void	ft_cd(char **command, char **env);
void	ft_exit(char **commands);
void	ft_export(char **commands, char **env);


#endif
