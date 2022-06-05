/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_metachar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:06:13 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/05 23:44:10 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file_content_all(int fd);
int		open_output_file(const char *file_name, int fg_append);

void	input_file_specify(t_cmd *cmd, t_list **token)
{
	int		input_fd;
	char	*file_name;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	file_name = (*token)->content;
	input_fd = open(file_name, O_RDONLY);
	if (input_fd == -1)
		perror(file_name);
	free(cmd->stdin_str);
	cmd->stdin_str = get_file_content_all(input_fd);
	close(input_fd);
}

void	heredoc(t_cmd *cmd, t_list **token)
{
	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	ft_lstadd_back(&(cmd->heredoc_end),
		ft_lstnew(ft_strdup((*token)->content)));
}

void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append)
{
	char			*file_name;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	file_name = (*token)->content;
	if (cmd->fd_out > STDERR_FILENO)
		close(cmd->fd_out);
	cmd->fd_out = open_output_file(file_name, fg_append);
}
