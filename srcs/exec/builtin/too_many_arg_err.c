/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   too_many_arg_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:19:04 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 22:30:17 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	too_many_arg_err(char *cmd_name)
{
	ft_putendl_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": too many arguments", STDERR_FILENO);
}