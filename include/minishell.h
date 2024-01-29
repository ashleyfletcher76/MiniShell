#ifndef MINISHELL
#define MINISHELL

#include "../libft/libft.h"
#include "pipex.h"

#include <readline/readline.h>
#include <readline/history.h>


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
}	t_mini;


void	freearr(char **arr);
char	*get_me_directory(t_mini *mini);
int		array_size(char **s);


#endif
