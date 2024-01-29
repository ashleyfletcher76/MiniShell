/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/29 15:08:26 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	array_size(char **s);
char *get_me_directory(void);


char *get_me_directory(void)
{
	char	cwd[PATH_MAX];
	char	**directories;
	char	*temp;
	int		x;
	
	getcwd(cwd, sizeof(cwd));
	directories = ft_split(cwd, '/');
	if (!directories)
	{
		//
		return (NULL);
	}
	x = array_size(directories);
	temp = ft_strjoin(directories[x - 1], " %");
	return (ft_strjoin("minishell ", temp));
}

int	array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}

int	main(void)
{
	int		i;
	char	*prompt;

	i = 0;
	while (1)
	{
		prompt = readline(get_me_directory());
		if (!prompt)
			add_history(prompt);

		free(prompt);
	}
	return (EXIT_SUCCESS);
}

