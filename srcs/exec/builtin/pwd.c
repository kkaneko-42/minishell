/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:06:30 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/05 23:36:36 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_cmd *input)
{
	char	*now_path;

	now_path = get_now_path();
	if (now_path == NULL)
		return (pwd_err());
	else
	{
		ft_putstr_fd(now_path, input->fd_out);
		ft_putstr_fd("\n", input->fd_out);
		free(now_path);
	}
	return (CMD_SUCCESS);
}
