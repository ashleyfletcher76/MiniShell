/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_adres.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:42:52 by muhakose          #+#    #+#             */
/*   Updated: 2024/03/01 13:25:51 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_adresses(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->env[i] != NULL)
	{
		if (ft_strlen(mini->env[i]) >= 5 && ft_strncmp(mini->env[i],
				"PATH=", 5) == 0)
			break ;
		i++;
	}
	if (mini->env[i])
	{
		mini->all_paths = ft_split(mini->env[i] + 5, ':');
		if (mini->all_paths == NULL)
			return (all_cleaner(mini), exit(EXIT_FAILURE));
	}
	else
	{
		mini->all_paths = ft_split("no path found.", ' ');
		if (mini->all_paths == NULL)
			return (all_cleaner(mini), exit(EXIT_FAILURE));
	}
}

char	*get_a_path(char *command, t_mini *mini)
{
	if (ft_strchr(command, '/') == NULL && command[0] != '\0')
		return (giveme_path(command, mini));
	else
	{
		file_check(command, mini);
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			error_handler(": command not found", mini, 126);
		}
		error_handler(": command not found", mini, 127);
	}
	exit(127);
}

char	*giveme_path(char *command, t_mini *mini)
{
	char	*path;
	char	*temp;
	int		j;

	j = -1;
	temp = ft_strjoin("/", command);
	while (mini->all_paths[++j])
	{
		path = ft_strjoin(mini->all_paths[j], temp);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				return (free(temp), path);
			}
			free(temp);
			free(path);
			error_handler(": command not found", mini, 126);
		}
		free(path);
	}
	free(temp);
	error_handler(": command not found", mini, 127);
	exit(127);
}

void	file_check(char *command, t_mini *mini)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			error_handler(": is a directory", mini, 126);
		else if (!(path_stat.st_mode & S_IXUSR))
			error_handler(": Permission denied", mini, 126);
	}
}
