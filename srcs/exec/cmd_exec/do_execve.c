/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 16:39:29 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/05 22:22:24 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_exec_args(t_cmd *input);
static char	**get_exec_envp(t_envp *envp);
static void	execute_from_path(char **path_env, t_cmd *input, t_envp *envp);
static void	execute_relative_absolute(t_cmd *input, t_envp *envp);

void	do_exexve(t_cmd *input, t_envp *envp)
{
	char	**path_env;

	path_env = ft_split(ft_getenv("PATH", envp), ':');
	if (path_env == NULL)
	{
		no_file_dir_err(input->name);
		exit(CMD_ERR);
	}
	if (input->name == NULL)
		exit(0);
	if (have_slash_symbol(input->name))
		execute_relative_absolute(input, envp);
	execute_from_path(path_env, input, envp);
	free_strs(path_env);
	path_env = NULL;
	cmd_not_found_err(input->name);
	exit(CHAR_MAX);
}

static void	execute_from_path(char **path_env, t_cmd *input, t_envp *envp)
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
		execve(path_cmd_search, exec_args, exec_envp);
		free(path_cmd_search);
		free_strs(exec_args);
		free_strs(exec_envp);
		++i;
	}
}

static void	execute_relative_absolute(t_cmd *input, t_envp *envp)
{
	char	**exec_args;
	char	**exec_envp;

	exec_args = get_exec_args(input);
	exec_envp = get_exec_envp(envp);
	execve(input->name, exec_args, exec_envp);
	free_strs(exec_args);
	free_strs(exec_envp);
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
