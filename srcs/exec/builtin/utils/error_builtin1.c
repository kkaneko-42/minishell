/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:19:04 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/30 00:00:31 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	too_many_args_err(char *cmd_name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
	return (CMD_ERR);
}

void	num_arg_required_err(char *exit_status)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(exit_status, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

int	identifier_err(char *cmd_name, char *content)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(content, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	return (CMD_ERR);
}

int	pwd_err(void)
{
	ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	errno = 0;
	return (CMD_ERR);
}
