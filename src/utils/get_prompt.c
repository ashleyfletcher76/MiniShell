/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:33:41 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 13:36:55 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*give_me_prompt(t_mini *mini)
{
	char	**directories;
	char	*temp;
	int		x;
	char	*user;

	user = getenv("USER");
	if (promt_help(mini, user) == 1)
		return (mini->prompt_msg);
	directories = ft_split(mini->cwd, '/');
	if (!directories)
		return (NULL);
	x = array_size(directories);
	temp = ft_strjoin(directories[x - 1], " % ");
	freearr(directories);
	mini->prompt_msg = ft_strjoin("@minishell ", temp);
	free(temp);
	temp = ft_strjoin(user, mini->prompt_msg);
	free(mini->prompt_msg);
	mini->prompt_msg = temp;
	return (mini->prompt_msg);
}

int	promt_help(t_mini *mini, char *user)
{
	char	cwd[PATH_MAX];
	char	*home;

	home = getenv("HOME");
	getcwd(cwd, sizeof(cwd));
	mini->cwd = ft_strdup(cwd);
	if (strcmp(cwd, "/") == 0)
	{
		mini->prompt_msg = ft_strjoin(user, "@minishell / % ");
		return (1);
	}
	if (strcmp(cwd, home) == 0)
	{
		mini->prompt_msg = ft_strjoin(user, "@minishell ~ % ");
		return (1);
	}
	return (0);
}
