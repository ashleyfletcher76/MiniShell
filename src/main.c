/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/30 13:37:53 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *get_me_directory(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	**directories;
	char	*temp;
	int		x;

	getcwd(cwd, sizeof(cwd));
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
	mini->prompt_msg = ft_strjoin("minishell ", temp);
	free(temp);
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
		prompt = readline(get_me_directory(&mini));
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

