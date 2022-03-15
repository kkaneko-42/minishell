/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/15 16:43:29 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_only_buitin(t_cmd *input);
static void		do_builtin(t_cmd *input, t_envp **envp);
static void		do_cmd(t_cmd *input, t_envp **envp);
static void		do_pipe(t_cmd *input, t_envp **envp, int n);
static void		set_output_to_stdout_or_fd_out(t_cmd *input, int fd[2], int from_right);
static void		set_input_from_stdin(t_cmd *input, int fd[2]);
static t_cmd	*should_be_done_cmd(t_cmd *input, int from_right);
static int		cmd_size(t_cmd *input);
static pid_t	fork_and_waitpid(void);
static int		last_output_is_not_stdout(t_cmd *input);
static t_cmd	*cmd_last(t_cmd *input);
static int		check_fork_err(pid_t pid);

void	exec(t_cmd *input, t_envp **envp)
{
	pid_t	pid;
	pid_t	pid2;

	if (is_only_buitin(input))
	{
		do_builtin(input, envp);
		return ;
	}
	pid = fork_and_waitpid();
	if (pid == 0)
	{
		/* pid2 = fork_and_waitpid();
		if (pid2 == 0)
		{ */
			if (last_output_is_not_stdout(input))
				dup2(cmd_last(input)->fd_out, 1);
			do_pipe(input, envp, 1);
			exit(1);
		/* }
		exit(1); */
	}
}

static int	is_only_buitin(t_cmd *input)
{
	if (cmd_size(input) != 1)
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


static void	do_builtin(t_cmd *input, t_envp **envp)
{
	if (!ft_strncmp(input->name, "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->name, "cd", 3))
		cd(input, *envp);
	else if (!ft_strncmp(input->name, "pwd", 4))
		pwd(input);
	else if (!ft_strncmp(input->name, "export", 7))
		export(input, *envp);
	else if (!ft_strncmp(input->name, "env", 4))
		env(input, *envp);
	else if (!ft_strncmp(input->name, "unset", 6))
		unset(input, envp);
	else if (!ft_strncmp(input->name, "exit", 5))
		exit(0);//exit???
}

static pid_t	fork_and_waitpid(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(-1);
	}
	waitpid(-1, &status, 0);
	if (status == -1)
		exit(-1);
	return (pid);
}

static int	last_output_is_not_stdout(t_cmd *input)
{
	if (cmd_last(input)->fd_out != 1)
		return (1);
	return (0);
}

static t_cmd	*cmd_last(t_cmd *input)
{
	t_cmd	*now;

	now = input;
	while (now->next != NULL)
		now = now->next;
	return (now);
}

static void	do_pipe(t_cmd *input, t_envp **envp, int from_right)
{
	pid_t	pid;
	int		status;
	int		fd[2];

	if (from_right == cmd_size(input))
		do_cmd(input, envp);
	else
	{
		pipe(fd);
		pid = fork_and_waitpid();
		if (pid == 0)
		{
			set_output_to_stdout_or_fd_out(input, fd, from_right);
			do_pipe(input, envp, from_right + 1);
		}
		else
		{
			set_input_from_stdin(input, fd);
			do_cmd(should_be_done_cmd(input, from_right), envp);
		}
	}
}

static void	set_output_to_stdout_or_fd_out(t_cmd *input, int fd[2], int from_right)
{
	t_cmd	*now;
	int		i;

	close(fd[0]);
	now = input;
	i = 0;
	while (i < cmd_size(input) - from_right - 1)
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

static void	set_input_from_stdin(t_cmd *input, int fd[2])
{
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
}

static t_cmd	*should_be_done_cmd(t_cmd *input, int from_right)
{
	int		i;
	t_cmd	*now;

	i = 0;
	now = input;
	while (i < cmd_size(input) - from_right)
	{
		now = now->next;
		++i;
	}
	return (now);
}

static void	do_cmd(t_cmd *input, t_envp **envp)
{
	if (input->name[0] == '\n')
		return ;
	if (!ft_strncmp(input->name, "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->name, "cd", 3))
		cd(input, *envp);
	else if (!ft_strncmp(input->name, "pwd", 4))
		pwd(input);
	else if (!ft_strncmp(input->name, "export", 7))
		export(input, *envp);
	else if (!ft_strncmp(input->name, "env", 4))
		env(input, *envp);
	else if (!ft_strncmp(input->name, "unset", 6))
		unset(input, envp);
	else if (!ft_strncmp(input->name, "exit", 5))
		exit(0);//exit???
	else
		do_exexve(input, *envp);
}

static int	cmd_size(t_cmd *input)
{
	int		i;
	t_cmd	*now;

	i = 0;
	now = input;
	while (now != NULL)
	{
		++i;
		now = now->next;
	}
	return (i);
}

/* 
static int	check_fork_err(pid_t pid)
{
	if (pid < 0)
	{
		perror("fork failed");
		exit(-1);
	}
	return
} */

/* 
static void	do_exexve(t_cmd *input, t_envp *envp)
{
	char	**path_env;
	size_t	i;
	char	*path_cmd_search;
	char	**exec_args;
	char	**exec_envp;

	if (get_path(envp) == NULL)
	{
		printf("minishell: %s: No such file or directory\n", input->name);
		return ;
	}
	path_env = ft_split(&get_path(envp)[5], ':');
	i = 0;
	while (path_env[i] != NULL)
	{
		path_cmd_search = three_strjoin(path_env[i], "/", input->name);
		exec_args = get_exec_args(input);
		exec_envp = get_exec_envp(envp);
		if (input->name[0] == '/')
			execve(input->name, exec_args, exec_envp);
		else
			execve(path_cmd_search, exec_args, exec_envp);
		free(path_cmd_search);
		free_strs(exec_args);
		free_strs(exec_envp);
		++i;
	}
	free_strs(path_env);
}

static char	*get_path(t_envp *envp)
{
	t_envp	*p;

	p = envp;
	while (p != NULL)
	{
		if (!ft_strncmp(p->content, "PATH=", 5))
			return (&(p->content)[5]);
		p = p->next;
	}
	return (NULL);
}

static char	*three_strjoin(char *s1, char *s2, char *s3)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	str = (char *)ft_xmalloc(sizeof(char) * (s1_len + s2_len + s3_len + 1));
	ft_memmove(str, s1, s1_len);
	ft_memmove(&str[s1_len], s2, s2_len);
	ft_memmove(&str[s1_len + s2_len], s3, s3_len);
	str[s1_len + s2_len + s3_len] = '\0';
	return (str);
}

static char	**get_exec_args(t_cmd *input)
{
	int		argc;
	char	**exec_args;
	t_list	*p_args;
	size_t	i;

	argc = ft_lstsize(input->args);
	exec_args = (char **)ft_xmalloc(sizeof(char *) * (argc + 2));
	exec_args[0] = (char *)ft_xmalloc(sizeof(char)
			* (ft_strlen(input->name) + 1));
	ft_memmove(exec_args[0], input->name, ft_strlen(input->name));
	p_args = input->args;
	i = 1;
	while (p_args != NULL)
	{
		exec_args[i] = (char *)ft_xmalloc(sizeof(char)
				* (ft_strlen(p_args->content) + 1));
		ft_memmove(exec_args[i], p_args->content, ft_strlen(p_args->content));
		exec_args[i][ft_strlen(p_args->content)] = '\0';
		p_args = p_args->next;
		++i;
	}
	exec_args[argc + 1] = NULL;
	return (exec_args);
}

static char	**get_exec_envp(t_envp *envp)
{
	int		argc;
	char	**exec_envp;
	t_envp	*p_envp;
	size_t	i;

	p_envp = envp;
	while (p_envp != NULL)
	{
		argc++;
		p_envp = p_envp->next;
	}
	exec_envp = (char **)ft_xmalloc(sizeof(char *) * (argc + 1));
	p_envp = envp;
	i = 0;
	while (p_envp != NULL)
	{
		exec_envp[i] = (char *)ft_xmalloc(sizeof(char)
				* (ft_strlen(p_envp->content) + 1));
		ft_memmove(exec_envp[i], p_envp->content, ft_strlen(p_envp->content));
		exec_envp[i][ft_strlen(p_envp->content)] = '\0';
		p_envp = p_envp->next;
		++i;
	}
	exec_envp[argc] = NULL;
	return (exec_envp);
}
 */
//cat libft/ft_strlen.c > test1 | ls > test2 | cat libft/ft_strlen.c | grep char