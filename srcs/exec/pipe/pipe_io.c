/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:15:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/05 23:35:06 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_output(t_cmd *input, int fd[2], int from_right)
{
	t_cmd	*now;
	int		i;

	close(fd[0]);
	now = input;
	i = 0;
	while (i < t_cmd_size(input) - from_right - 1)
	{
		now = now->next;
		++i;
	}
	if (now->fd_out == 1)
		dup2(fd[1], 1);
	else
		dup2(now->fd_out, 1);
	close(fd[1]);
}

void	set_input(t_cmd *input, int fd[2], int from_right)
{
	t_cmd	*now;
	int		i;

	close(fd[1]);
	now = input;
	i = 0;
	while (i < t_cmd_size(input) - from_right)
	{
		now = now->next;
		++i;
	}
	if (now->stdin_str == NULL)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		set_input_from_redirection(now->stdin_str);
	}
}

void	set_input_from_redirection(const char *stdin_str)
{
	int	fd[2];

	pipe(fd);
	write(fd[1], stdin_str, ft_strlen(stdin_str) + 1);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}
