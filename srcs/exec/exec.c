/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 23:46:03 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_only_buitin(t_cmd *input);
static int		do_cmd(t_cmd *input, t_envp **envp);
static void		do_pipe(t_cmd *input, t_envp **envp, int n);
static void		set_input_from_redirection(const char *stdin_str);
static void		set_output(t_cmd *input, int fd[2], int from_right);
static void		set_input(t_cmd *input, int fd[2], int from_right);
static t_cmd	*should_be_done_cmd(t_cmd *input, int from_right);
static pid_t	fork_and_waitpid(void);
static int		last_output_is_not_stdout(t_cmd *input);
static int		check_fork_err(pid_t pid);
static pid_t	fork_and_err(void);
static void		set_question_mark_env(t_envp *envp, int end_status);
static int		waitpid_and_err(pid_t pid);

void	exec(t_cmd *input, t_envp **envp)
{
	pid_t	pid;
	int		status;

	if (is_only_buitin(input))
		status = do_cmd(input, envp);
	else
	{
		status = 0;
		pid = fork_and_err();
		if (pid == 0)
		{
			if (last_output_is_not_stdout(input))
				dup2(t_cmd_last(input)->fd_out, 1);
			do_pipe(input, envp, 1);
			exit(1);
		}
		status = waitpid_and_err(pid);
		status = WEXITSTATUS(status);
	}
	set_question_mark_env(*envp, status);
}

static int	waitpid_and_err(pid_t pid)
{
	int status;

	status = 0;
	if (waitpid(pid, &status, 0) == WAIT_ERR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(WAIT_ERR);
	}
	return (status);
}

static void	set_question_mark_env(t_envp *envp, int end_status)
{
	char	*end_status_str;
	char	*new_end_status_env;

	end_status_str = ft_itoa(end_status);
	new_end_status_env = ft_strjoin("?=", end_status_str);
	free(end_status_str);
	delete_env(&envp, "?");
	addback_envp_list(&envp, new_end_status_env);
	free(new_end_status_env);
}

static int	is_only_buitin(t_cmd *input)
{
	if (t_cmd_size(input) != 1)
		return (0);
	if (!ft_strncmp(input->name, "echo", 5))
		return (1);
	else if (!ft_strncmp(input->name, "cd", 3))
		return (1);
	else if (!ft_strncmp(input->name, "pwd", 4))
		return (1);
	else if (!ft_strncmp(input->name, "export", 7))
		return (1);
	else if (!ft_strncmp(input->name, "env", 4))
		return (1);
	else if (!ft_strncmp(input->name, "unset", 6))
		return (1);
	else if (!ft_strncmp(input->name, "exit", 5))
		return (1);
	return (0);
}

static pid_t	fork_and_waitpid(void)
{
	pid_t	pid;
	int		status;

	pid = fork_and_err();
	if (pid != 0)
		status = waitpid_and_err(pid);
	return (pid);
}

static int	last_output_is_not_stdout(t_cmd *input)
{
	if (t_cmd_last(input)->fd_out != 1)
		return (1);
	return (0);
}

static void	do_pipe(t_cmd *input, t_envp **envp, int from_right)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (from_right == t_cmd_size(input))
	{
		if (input->stdin_str != NULL)
			set_input_from_redirection(input->stdin_str);
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

static void	set_input_from_redirection(const char *stdin_str)
{
	int	fd[2];

	pipe(fd);
	write(fd[1], stdin_str, ft_strlen(stdin_str) + 1);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
}

static void	set_output(t_cmd *input, int fd[2], int from_right)
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

static void	set_input(t_cmd *input, int fd[2], int from_right)
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

static int	do_cmd(t_cmd *input, t_envp **envp)
{
	int	ret;

	ret = 0;
	if (!ft_strncmp(input->name, "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->name, "cd", 3))
		ret = cd(input, *envp);
	else if (!ft_strncmp(input->name, "pwd", 4))
		ret = pwd(input);
	else if (!ft_strncmp(input->name, "export", 7))
		ret = export(input, *envp);
	else if (!ft_strncmp(input->name, "env", 4))
		ret = env(input, *envp);
	else if (!ft_strncmp(input->name, "unset", 6))
		ret = unset(input, envp);
	else if (!ft_strncmp(input->name, "exit", 5))
		exit_builtin(input);
	else
		do_exexve(input, *envp);
	return (ret);
}

static pid_t	fork_and_err(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == FORK_ERR)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(FORK_ERR);
	}
	return (pid);
}
