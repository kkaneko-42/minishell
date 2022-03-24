/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:33:30 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 16:55:54 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

pid_t	fork_and_err(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FORK_ERR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		errno = 0;
		exit(FORK_ERR);
	}
	return (pid);
}

int	waitpid_and_err(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) == WAIT_ERR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		errno = 0;
		exit(WAIT_ERR);
	}
	return (status);
}

pid_t	fork_and_waitpid(void)
{
	pid_t	pid;
	int		status;

	pid = fork_and_err();
	if (pid != 0)
		status = waitpid_and_err(pid);
	return (pid);
}
