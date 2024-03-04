/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:43:47 by asfletch          #+#    #+#             */
/*   Updated: 2024/03/04 10:46:54 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

extern int	g_signal_flag;

//main nessecaries
void		prompt_init(t_mini *mini, int exit_code);
int			main(int ac, char **av, char **env);
void		struct_init(t_mini *mini, char **env);

//parsing full
void		parse_init(t_mini *mini);
void		parse_distributor(t_mini *mini, t_commands *command, int i, int j);
void		finalize_cmd(char **temp, int *j, t_commands **cmd, int indicator);
void		add_cmd_args(t_commands *cmd, char **temp, int *j);
char		*check_other_cmds(t_mini *mini, t_commands *cmd,
				char *temp, int *i);
//quotes
char		*parse_double_quote(t_mini *mini, int *i);
char		*dquote_helper(char *quoted_str);
char		*parse_single_quote(t_mini *mini, int *i);
char		*quote_helper(char *quoted_str);
char		*append_heredoc(t_mini *mini, char *temp);
char		*full_heredoc(t_mini *mini, char *orig_str, char *new_str,
				int first_line);
char		*handle_dollar_heredoc(t_mini *mini, char *prompt, int *i);
char		*dollar_helper_here(int *i, char *new_temp, char *prompt);;
char		*check_expand_heredoc(t_mini *mini, char *temp);
char		*parse_double_heredoc(t_mini *mini, int *i);
//input and output
void		parse_input(t_mini *mini, int *i, t_commands **cmd);
void		parse_output(t_mini *mini, int *i, t_commands **cmd);
void		update_input_arg(t_commands **cmd, char **temp, int flag);
void		update_output_arg(t_commands **cmd, char **temp, int flag);
//dollar
char		*handle_dollar(t_mini *mini, int *i);
char		*dollar_helper(t_mini *mini, int *i, char *new_temp);
char		*dollar_inside_quotes(t_mini *mini, int *i, char *quoted_str);
char		*dollar_quotes_helper(t_mini *mini, char *temp_env, int *i);
//linked list
void		lstadd_back(t_commands **lst, t_commands *new_node);
t_commands	*lstnew(void);
t_commands	*lstlast(t_commands *lst);

//builtin full
int			is_built_in(t_mini *mini);
int			which_build(char **commands, char **env, t_mini *mini);
int			exist_build(char **commands);
int			checkpathexistence(const char *path);
//pwd
void		ft_pwd(t_mini *mini);
void		update_pwd_env(t_mini *mini);
void		update_pwd_envhelp(t_mini *mini, char *cwd);
void		update_oldpwd_env(t_mini *mini, char *temp);
void		update_oldpwd_env_part_2(t_mini *mini, char *temp, int i);
//cd
void		ft_cd(char **command, char **env, t_mini *mini);
void		ft_cd_oldpwd(t_mini *mini);
void		ft_cd_error(t_mini *mini, char *command);
void		ft_cd_use_home(char *home, char *command);
//exit
void		ft_exit(char **commands, t_mini *mini);
int			ft_exit_helper(char *code);
//export
void		ft_export(char **commands, t_mini *mini);
int			ft_export_loop(char *commands, t_mini *mini);
int			ft_export_error(t_mini *mini, char *commands);
int			ft_count_equal(char *s);
void		ft_export_helper(char *commands, t_mini *mini, char *var);
void		append_export(char *comds, t_mini *mini);
void		normal_export(char *comds, t_mini *mini);
void		export_error_message(t_mini *mini, char *cmds, int flag);
void		bouble_sort_char(char **export);
char		**dup_export(char **env);
char		*export_style(char	*s);
void		add_append_export(char *comds, t_mini *mini);
void		add_export(char *comds, t_mini *mini);
void		add_export_helper(char *commands, t_mini *mini, char *var);
char		*export_style_append(char *s);
int			if_check(char *s, char *p);
//unset
int			ft_unset_loop(char *commands, char **env, t_mini *mini);
int			ft_export_unset_loop(char *commands, t_mini *mini);
void		ft_unset(char **commands, char **env, t_mini *mini);
int			check_variable(char *s);
//echo_env
void		ft_env(char **env, t_mini *mini);
void		ft_echo(char **commands, t_mini *mini);
int			echo_n(char *s);

//exec full
void		exec_init(t_mini *mini);
void		exec_main(t_mini *mini);
void		pipe_all(t_mini *mini);
void		pipe_close(t_mini *mini);
//children
void		only_child(t_mini *mini, int i);
void		first_son(t_mini *mini, int i);
void		last_son(t_mini *mini, int i);
void		daughters(t_mini *mini, int i);
void		piper(t_mini *mini);
//exec utils
void		forker(t_mini *mini, int i);
void		get_adresses(t_mini *mini);
char		*giveme_path(char *command, t_mini *mini);
char		*get_a_path(char *command, t_mini *mini);
void		file_check(char *command, t_mini *mini);

//direction full
void		direction_handler(t_mini *mini);
//input
void		input_handler(t_mini *mini, int input);
void		output_dup2(int input, t_mini *mini);
void		input_dup2(int input, t_mini *mini);
int			input_opener(t_mini *mini, char *s);
void		dup_saver_input(t_mini *mini);
void		heredoc_found(t_mini *mini, int input);
int			check_input_direction(char *s);
//output
void		output_handler(t_mini *mini, int output);
int			output_opener(t_mini *mini, char *s);
int			output_append_opener(t_mini *mini, char *s);
void		dup_saver_output(t_mini *mini);
int			check_output_direction(char *s);

//utils full
//tools
char		*ft_char_join(char *s1, char c);
void		*ft_realloc(void *ptr, int old_size, int new_size);
char		*ft_strndup(const char *s1, size_t nbr);
char		**ft_realloc_char(char **ptr, int j);
int			*ft_realloc_int(int *ptr, int j);
int			array_size(char **s);
int			commands_size_all(t_commands *lst);
int			commands_size_buildin(t_commands *lst);
int			token_dollor(char c);
int			token_dollor_first(char c);
void		waiter(t_mini *mini);
int			check_syntax(t_mini *mini);
int			check_pipe(char *s);
int			if_check(char *s, char *p);
//env
char		*get_env(char **env, char *var);
char		**update_env(char **env, char *var, char *value);
char		**dup_env(char **env);
//skip
int			skip_quotes(char *s, int i);
int			skip_whitespace(char c);
int			no_whitespace_skip(char c);

//error full
void		error_handler(char *msg, t_mini *mini, int exitcode);
void		error_message(int flag);

//cleaning full
void		all_cleaner(t_mini *mini);
void		configure_terminal(void);
void		sigint_handler(int sig);
void		sig_init(void);
void		commands_cleaner(t_commands *commds);
void		cleaner(t_mini *mini);
//free
void		free_struct(t_mini *mini);
void		free_double_int(int **array, int num_cmds);
void		free_double_array(char **array);
void		freearr(char **arr);

void		print_commands(t_mini *mini);

#endif
