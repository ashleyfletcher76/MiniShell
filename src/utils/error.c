/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 09:39:53 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/28 09:40:08 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error_message(t_pipex *pipex, char *cmds, int flag)
{
	if (flag == 0)
		ft_put3endl_fd("minishell: export: `", cmds,
			"': not a valid identifier", 2);
	else if (flag == 1)
		ft_put3endl_fd("minishell: unset: `",
			cmds, "': not a valid identifier", 2);
	pipex->exitcode = 1;
}