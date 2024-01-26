/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_adres.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:42:52 by muhakose          #+#    #+#             */
/*   Updated: 2024/01/26 17:50:26 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

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
		pipex->all_paths = ft_split(pipex->av[i], ' ');
		if (pipex->all_paths == NULL)
			return (free_struct(pipex), exit(EXIT_FAILURE));
	}
}

void	check_args(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->command_paths = (char ***)malloc((pipex->nbr_cmd + 1)
			* sizeof(char **));
	while (i < pipex->nbr_cmd)
	{
		pipex->command_paths[i] = ft_split(pipex->av[i + 2], ' ');
		i++;
	}
	pipex->command_paths[i] = NULL;
}

char	*get_a_path(char *command, t_pipex *pipex, int i)
{
	if (ft_strchr(command, '/') == NULL)
		return (giveme_path(command, pipex, i));
	else
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
			{
				return (command);
			}
			error_handler(": command not found", pipex, i, 126);
		}
		error_handler(": command not found", pipex, i, 127);
	}
	exit(127);
}

char	*giveme_path(char *command, t_pipex *pipex, int i)
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
			error_handler(": command not found", pipex, i, 126);
		}
		free(path);
	}
	free(temp);
	error_handler(": command not found", pipex, i, 127);
	exit(127);
}
