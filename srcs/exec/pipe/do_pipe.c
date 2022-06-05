/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:43:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/06 01:22:57 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*should_be_done_cmd(t_cmd *input, int from_right);

void	do_pipe(t_cmd *input, t_envp **envp, int from_right)
{
	pid_t	pid;
	int		fd[2];

	if (from_right == t_cmd_size(input))
	{
		if (input->stdin_str != NULL || input->heredoc_end != NULL)
			set_input_from_redirection(input);
		do_cmd(input, envp);
	}
	else
	{
		pipe(fd);
		pid = fork_and_waitpid();
		if (pid == 0)
		{
			set_output(input, fd, from_right);
			do_pipe(input, envp, from_right + 1);
		}
		else
		{
			set_input(input, fd, from_right);
			do_cmd(should_be_done_cmd(input, from_right), envp);
		}
	}
}

static t_cmd	*should_be_done_cmd(t_cmd *input, int from_right)
{
	int		i;
	t_cmd	*now;

	i = 0;
	now = input;
	while (i < t_cmd_size(input) - from_right)
	{
		now = now->next;
		++i;
	}
	return (now);
}
