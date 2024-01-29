/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:11:20 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/29 12:08:38 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	array_size(char **s);

int	main(void)
{
	int		i;
	int		x;
	char	cwd[PATH_MAX];
	char	**s;
	char *prompt;


	i = 0;
	getcwd(cwd, sizeof(cwd));
	while (1)
	{
		s = ft_split(cwd, '/');
		x = array_size(s);
		printf("%s ", s[x - 3]);
		prompt = readline("minishell % ");

		for (int j = 0; j < x; j++)
		{
			free(s[j]);
		}
		free(s);
	}
	return (EXIT_SUCCESS);
}

int	array_size(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		i++;
	return (i);
}
