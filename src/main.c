/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/29 15:33:47 by muhakose         ###   ########.fr       */
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

int	main(void)
{
	int		i;
	char	*prompt;
	t_mini	mini;

	i = 0;
	while (1)
	{
		prompt = readline(get_me_directory(&mini));
		if (!prompt)
			exit(EXIT_FAILURE);
		add_history(prompt);

		free(prompt);
	}
	clear_history();
	return (EXIT_SUCCESS);
}

