/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakose <muhakose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:30:52 by muhakose          #+#    #+#             */
/*   Updated: 2024/02/24 12:10:44 by muhakose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*buff_to_line(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	if (!temp)
		return (NULL);
	free(buffer);
	return (temp);
}

char	*readyfornext(char *s)
{
	char	*temp;
	int		i;
	int		newlen;
	int		delete;

	newlen = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	delete = i + 1;
	while (s[i++])
		newlen++;
	temp = malloc (newlen + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (newlen > 0)
	{
		temp[i++] = s[delete++];
		newlen--;
	}
	temp[i] = '\0';
	free(s);
	return (temp);
}

char	*line_line(char *s)
{
	char	*line;
	int		i;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] && s[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_text(char *s, int fd)
{
	int		byte_size;
	char	*buf;

	byte_size = 1;
	buf = malloc (BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (byte_size > 0)
	{
		byte_size = read(fd, buf, BUFFER_SIZE);
		buf[byte_size] = '\0';
		s = buff_to_line(s, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	if (byte_size <= 0 && s[0] == '\0')
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*get_next_line(int fd)
{
	static char		*all_line;
	char			*next_line;

	if (!all_line)
	{
		all_line = ft_calloc(1, 1);
		if (!all_line)
			return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(all_line);
		all_line = NULL;
		return (NULL);
	}
	all_line = read_text(all_line, fd);
	if (!all_line)
		return (NULL);
	next_line = line_line(all_line);
	all_line = readyfornext(all_line);
	return (next_line);
}

/* int main(void)
{
	int fd;
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	line = get_next_line(7);
	printf ("%s", line);
	free(line);

	close(fd);
	return 0;
} */
