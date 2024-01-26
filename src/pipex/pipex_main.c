/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:36:00 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/26 17:50:38 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

int	pipex_main(int ac, char **av, char **env)
{
	t_pipex	pipex;

	if (ac >= 5)
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
