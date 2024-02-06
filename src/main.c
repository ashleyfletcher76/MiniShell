/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/05 10:54:06 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *give_me_prompt(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	**directories;
	char	*temp;
	int		x;
	char	*home;
	char	*user;

	user = getenv("USER");
	home = getenv("HOME");

	getcwd(cwd, sizeof(cwd));
	if (strcmp(cwd, home) == 0)
		return (ft_strjoin(user, "@minishell ~ % "));
	mini->cwd = cwd;
	directories = ft_split(cwd, '/');
	if (!directories)
	{
		freearr(directories);
		return (NULL);
	}
	x = array_size(directories);
	temp = ft_strjoin(directories[x - 1], " % ");
	freearr(directories);
	mini->prompt_msg = ft_strjoin("@minishell ", temp);
	free(temp);
	temp = ft_strjoin(user, mini->prompt_msg);
	free(mini->prompt_msg);
	mini->prompt_msg = temp;
	return (mini->prompt_msg);
}



int	main(int ac, char **av, char **env)
{
	int		i;
	char	*prompt;
	t_mini	mini;

	mini.env = env;
	i = 0;
	while (1)
	{
		prompt = readline(give_me_prompt(&mini));
		if (!prompt)
			exit(EXIT_FAILURE);
		add_history(prompt);
		mini.prompt = prompt;
		parse_init(&mini);
		free(prompt);
		
	}
	(void)ac;
	(void)av;
	clear_history();
	return (EXIT_SUCCESS);
}
