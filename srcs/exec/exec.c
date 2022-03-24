/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 23:59:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		is_only_buitin(t_cmd *input);
static int		last_output_is_not_stdout(t_cmd *input);
static void		set_question_mark_env(t_envp *envp, int end_status);

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

static int	last_output_is_not_stdout(t_cmd *input)
{
	if (t_cmd_last(input)->fd_out != 1)
		return (1);
	return (0);
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
