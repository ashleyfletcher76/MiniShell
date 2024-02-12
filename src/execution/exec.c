/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:30:56 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/12 09:28:16 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_init(t_mini *mini)
{
	char **argv = NULL;

	argv = ft_split(mini->prompt, '\"');
	argv = ft_split(mini->prompt, '|');
	mini->argv = argv;

	is_built_in(mini);


}
