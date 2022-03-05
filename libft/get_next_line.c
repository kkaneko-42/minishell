/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:38:08 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/02/11 15:36:01 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*make_save(int fd, char *save)
{
	char	*buf;
	char	*tmp;
	int		read_len;

	buf = (char *)ft_xmalloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	read_len = 1;
	while (ft_strchr(save, '\n') == NULL && read_len != 0)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_len] = '\0';
		tmp = save;
		save = ft_strjoin(save, buf);
		free(tmp);
		tmp = NULL;
	}
	free(buf);
	return (save);
}

static char	*make_line(char *save)
{
	int		line_len;
	char	*line;

	if (save[0] == '\0')
		return (NULL);
	line_len = 0;
	while (save[line_len] != '\0' && save[line_len] != '\n')
		line_len++;
	if (save[line_len] == '\n')
		line = (char *)ft_xmalloc(sizeof(char) * (line_len + 2));
	else
		line = (char *)ft_xmalloc(sizeof(char) * (line_len + 1));
	if (line == NULL)
		return (NULL);
	if (save[line_len] == '\n')
	{
		ft_memmove(line, save, line_len + 1);
		line_len++;
	}
	else
		ft_memmove(line, save, line_len);
	line[line_len] = '\0';
	return (line);
}

static char	*trim_save(char *save, char *line)
{
	char	*save_new;
	size_t	save_len;
	size_t	line_len;

	if (line == NULL)
	{
		free(save);
		return (NULL);
	}
	save_len = ft_strlen(save);
	line_len = ft_strlen(line);
	if (save[line_len] == '\0')
	{
		free(save);
		return (NULL);
	}
	save_new = (char *)ft_xmalloc(sizeof(char) * (save_len - line_len + 1));
	if (save_new == NULL)
		return (NULL);
	ft_memmove(save_new, &save[line_len], save_len - line_len);
	save_new[save_len - line_len] = '\0';
	free(save);
	return (save_new);
}

char	*get_next_line(int fd)
{
	static char	*save[259];
	char		*line;

	if (fd < 0 || 259 <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = make_save(fd, save[fd]);
	if (save[fd] == NULL)
	{
		free(save[fd]);
		return (NULL);
	}
	line = make_line(save[fd]);
	save[fd] = trim_save(save[fd], line);
	return (line);
}
