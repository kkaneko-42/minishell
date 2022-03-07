/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/07 23:44:24 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_cmd(t_cmd *input, t_envp *envp);
static void	do_pipe(t_cmd *input, t_envp *envp, int n);
static int	cmd_lstsize(t_cmd *input);

void	exec(t_cmd *input, t_envp **envp)
{
	if (input->name[0] == '\n')
		return ;
	if (!ft_strncmp(input->name, "echo", 5))
		echo(input);
	else if (!ft_strncmp(input->name, "cd", 3))
		cd(input);
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
		do_cmd(input, *envp);
}

static void	do_cmd(t_cmd *input, t_envp *envp)
{
	pid_t	pid;

	pid = fork();
	wait(NULL);
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
	{
		do_pipe(input, envp, 1);
		printf("minishell: %s: command not found\n", input->name);
		exit(1);
	}
}


static void	do_pipe(t_cmd *input, t_envp *envp, int n)
{
	pid_t	pid;
	int		fd[2];
	int		i;
	t_cmd	*now;
	
	if (n == cmd_lstsize(input))
	{
		do_exexve(input, envp);
	}
	else
	{
		pipe(fd);
		pid = fork();
		wait(NULL);
		if (pid == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			do_pipe(input, envp, n + 1);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			i = 0;
			now = input;
			while (i < cmd_lstsize(input) - n)
			{
				now = now->next;
				++i;
			}
			do_exexve(now, envp);
		}
	}
	/* pid = fork();
	wait(NULL);
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
	{
		do_(input, envp, 0);
		printf("minishell: %s: command not found\n", input->name);
		exit(1);
	}*/
}

//static void	do_pipe(t_cmd *input, t_envp *envp, int n)

static int	cmd_lstsize(t_cmd *input)
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