/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:49:10 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 00:56:47 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	do_cmd(t_cmd *input, t_envp **envp)
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
		ret = exit_builtin(input);
	else
		do_exexve(input, *envp);
	return (ret);
}
