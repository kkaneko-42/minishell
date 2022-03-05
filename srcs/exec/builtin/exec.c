/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/04 19:43:59 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec(t_cmd *input, t_envp **envp)
{
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
		;//exit 未完成
}
