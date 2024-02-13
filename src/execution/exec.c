/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/12 17:01:40 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_init(t_mini *mini)
{

	exec_main(mini);

}

void	exec_main(t_mini *mini)
{
	t_pipex	pipex;

	pipex.nbr_cmd = ft_lstsize_t_cmds(mini->commands);
	pipex.env = mini->env;
	pipex.commands = mini->commands;
	get_adresses(&pipex);
	pipe_all(&pipex);
	pipe_close(&pipex);
	waiter(&pipex);
	
	//free_struct(&pipex);
}
