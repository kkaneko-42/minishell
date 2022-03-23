/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:39:29 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 23:01:38 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_path(t_envp *envp);
static char	**get_exec_args(t_cmd *input);
static char	**get_exec_envp(t_envp *envp);
static void	search_from_path_and_execute(
				char **path_env, t_cmd *input, t_envp *envp);

void	do_exexve(t_cmd *input, t_envp *envp)
{
	char	**path_env;
	size_t	i;
	char	*path_cmd_search;
	char	**exec_args;
	char	**exec_envp;

	if (get_path(envp) == NULL)
	{
		printf("minishell: %s: No such file or directory\n", input->name);
		exit(1);
	}
	path_env = ft_split(get_path(envp), ':');
	search_from_path_and_execute(path_env, input, envp);
	free_strs(path_env);
	path_env = NULL;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(input->name, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(1);
}

static void	search_from_path_and_execute(
				char **path_env, t_cmd *input, t_envp *envp)
{
	size_t	i;
	char	*path_cmd_search;
	char	**exec_args;
	char	**exec_envp;

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
	ft_memmove(exec_args[0], input->name, ft_strlen(input->name) + 1);
	p_args = input->args;
	i = 1;
	while (p_args != NULL)
	{
		exec_args[i] = (char *)ft_xmalloc(sizeof(char)
				* (ft_strlen(p_args->content) + 1));
		ft_memmove(exec_args[i], p_args->content,
			ft_strlen(p_args->content) + 1);
		p_args = p_args->next;
		++i;
	}
	exec_args[argc + 1] = NULL;
	return (exec_args);
}

static char	**get_exec_envp(t_envp *envp)
{
	const int	argc = count_env_lstsize(envp);
	char		**exec_envp;
	t_envp		*p_envp;
	size_t		i;

	exec_envp = (char **)ft_xmalloc(sizeof(char *) * (argc + 1));
	p_envp = envp;
	i = 0;
	while (p_envp != NULL)
	{
		exec_envp[i] = (char *)ft_xmalloc(sizeof(char)
				* (ft_strlen(p_envp->content) + 1));
		ft_memmove(exec_envp[i],
			p_envp->content,
			ft_strlen(p_envp->content) + 1);
		p_envp = p_envp->next;
		++i;
	}
	exec_envp[argc] = NULL;
	return (exec_envp);
}
