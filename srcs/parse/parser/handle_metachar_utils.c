/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_metachar_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 00:01:18 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/05 19:40:22 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

char	*get_heredoc_input(t_list *heredoc_end)
{
	char	*line;
	char	*res;

	res = NULL;
	line = NULL;
	while (heredoc_end != NULL)
	{
		free(res);
		res = ft_strdup("");
		line = readline(HEREDOC_PROMPT);
		while (line != NULL
			&& ft_strncmp(line, heredoc_end->content,
				ft_strlen(heredoc_end->content) + 1) != 0)
		{
			res = ft_stradd(&res, line);
			res = ft_stradd(&res, "\n");
			free(line);
			line = readline(HEREDOC_PROMPT);
		}
		heredoc_end = heredoc_end->next;
	}
	free(line);
	return (res);
}

char	*get_file_content_all(int fd)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		res = ft_stradd(&res, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (res);
}

int	open_output_file(const char *file_name, int fg_append)
{
	const mode_t	out_file_rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int		open_flags = O_RDWR | O_CREAT | fg_append;
	int				res;

	if (fg_append != O_APPEND)
	{
		if (unlink(file_name) && errno != ENOENT)
			perror(file_name);
	}
	res = open(file_name, open_flags, out_file_rights);
	if (res == -1)
		perror(file_name);
	return (res);
}
