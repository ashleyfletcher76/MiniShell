/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:36:00 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/01 12:20:34 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	pipex_main(char **av, char **env)
{
	t_pipex	pipex;

	pipex.nbr_cmd = array_size(av);
	pipex.env = env;
	pipex.av = av;
	//pipex.input = av[1];
	//pipex.output = av[ac -1];
	get_adresses(&pipex);
	pipe_all(&pipex);
	pipe_close(&pipex);
	waiter(&pipex);
	//free_struct(&pipex);
	
}
