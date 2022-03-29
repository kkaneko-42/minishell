/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_builtin2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:19:04 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/30 00:00:37 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

int	no_old_pwd_err(void)
{
	ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
	return (CMD_ERR);
}

int	cd_err(t_cmd *input)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (input->args != NULL)
	{
		ft_putstr_fd(input->args->content, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	errno = 0;
	return (CMD_ERR);
}
