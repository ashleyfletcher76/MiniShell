/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_adres.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asfletch <asfletch@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:42:52 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/27 14:30:31 by asfletch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_adresses(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env[i] != NULL)
	{
		if (ft_strlen(pipex->env[i]) >= 5 && ft_strncmp(pipex->env[i],
				"PATH=", 5) == 0)
			break ;
		i++;
	}
	if (pipex->env[i])
	{
		pipex->all_paths = ft_split(pipex->env[i] + 5, ':');
		if (pipex->all_paths == NULL)
			return (free_struct(pipex), exit(EXIT_FAILURE));
	}
	else
	{
		pipex->all_paths = ft_split("no path found.", ' ');
		if (pipex->all_paths == NULL)
			return (free_struct(pipex), exit(EXIT_FAILURE));
	}
}

char	*get_a_path(char *command, t_pipex *pipex)
{
	if (ft_strchr(command, '/') == NULL && command[0] != '\0')
		return (giveme_path(command, pipex));
	else
	{
		file_check(command, pipex);
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (command);
			error_handler(": command not found", pipex, 126);
		}
		error_handler(": command not found", pipex, 127);
	}
	exit(127);
}

char	*giveme_path(char *command, t_pipex *pipex)
{
	char	*path;
	char	*temp;
	int		j;

	j = -1;
	temp = ft_strjoin("/", command);
	while (pipex->all_paths[++j])
	{
		path = ft_strjoin(pipex->all_paths[j], temp);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				return (free(temp), path);
			}
			free(temp);
			free(path);
			error_handler(": command not found", pipex, 126);
		}
		free(path);
	}
	free(temp);
	error_handler(": command not found", pipex, 127);
	exit(127);
}

void	file_check(char *command, t_pipex *pipex)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			error_handler(": is a directory", pipex, 126);
		else if (!(path_stat.st_mode & S_IXUSR))
			error_handler(": Permission denied", pipex, 126);
	}
}
