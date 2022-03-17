/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_metachar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:06:13 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/17 19:54:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_heredoc_input(const char *end_text);
static char	*get_file_content_all(int fd);

void	input_file_specify(t_cmd *cmd, t_list **token)
{
	int		input_fd;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	input_fd = open((*token)->content, O_RDONLY);
	if (input_fd == -1)
		; //open err
	cmd->stdin_str = get_file_content_all(input_fd);
}

void	heredoc(t_cmd *cmd, t_list **token)
{
	char	*end_text;
	char	*line;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	end_text = (*token)->content;
	cmd->stdin_str = get_heredoc_input(end_text);
}

static char	*get_heredoc_input(const char *end_text)
{
	char	*line;
	char	*res;

	res = NULL;
	line = readline(HEREDOC_PROMPT);
	while (line != NULL
		&& ft_strncmp(line, end_text, ft_strlen(end_text) + 1) != 0)
	{
		res = ft_stradd(&res, line);
		res = ft_stradd(&res, "\n");
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	//eof validation
	free(line);
	return (res);
}

void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append)
{
	const mode_t	out_file_rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int		open_flags = O_RDWR | O_CREAT | fg_append;
	char			*file_name;
	int				fd_out;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	file_name = (*token)->content;
	if (fg_append != O_APPEND)
	{
		if (unlink(file_name) && errno != ENOENT)
			perror(file_name);
	}
	//other flags(eg:O_CLOEXEC) may be needed
	fd_out = open(file_name, open_flags, out_file_rights);
	if (fd_out == -1)
		perror(file_name);
	cmd->fd_out = fd_out;
}

static char	*get_file_content_all(int fd)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = get_next_line(fd);
	while (tmp != NULL) //EOF?error?
	{
		res = ft_stradd(&res, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (res);
}
