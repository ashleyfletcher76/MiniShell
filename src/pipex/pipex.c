/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:10:32 by muhakose          #+#    #+#             */
/*   Updated: 2023/12/13 16:48:33 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac == 5)
	{
		pipex.nbr_cmd = ac - 3;
		pipex.env = env;
		pipex.av = av;
		pipex.input = av[1];
		pipex.output = av[ac -1];
		get_adresses(&pipex);
		check_args(&pipex);
		pipe_all(&pipex);
		pipe_close(&pipex);
		waiter(&pipex);
		free_struct(&pipex);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
