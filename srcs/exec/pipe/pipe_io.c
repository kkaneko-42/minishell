/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:15:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/06 00:32:48 by okumurahyu       ###   ########.fr       */
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
	//now->stdin_str = get_heredoc_input(now->heredoc_end);
	if (now->heredoc_end == NULL)
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		set_input_from_redirection(now);
	}
}

void	set_input_from_redirection(t_cmd *input)
{
	int		fd[2];
	int		pid;
	char	*heredoc_str;

	heredoc_str = NULL;
	pipe(fd);
	if (input->heredoc_end != NULL)
	{
		pid = fork_and_waitpid();
		if (pid == 0)
		{
			heredoc_str = get_heredoc_input(input->heredoc_end);
			if (input->stdin_str != NULL)
				write(fd[1], input->stdin_str, ft_strlen(input->stdin_str) + 1);
			else
				write(fd[1], heredoc_str, ft_strlen(heredoc_str) + 1);
			free(heredoc_str);
			exit(0);
		}
	}
	else
		write(fd[1], input->stdin_str, ft_strlen(input->stdin_str) + 1);
	//write(fd[1], stdin_str, ft_strlen(stdin_str) + 1);
	/* if (input->stdin_str != NULL)
		write(fd[1], input->stdin_str, ft_strlen(input->stdin_str) + 1);
	else
	{
		pid = fork_and_waitpid();
		if (pid == 0)
		{
			input->stdin_str = get_heredoc_input(input->heredoc_end);
			write(fd[1], input->stdin_str, ft_strlen(input->stdin_str) + 1);
			exit(0);
		}
	} */
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}
