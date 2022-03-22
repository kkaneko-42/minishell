/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:06:30 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/22 12:46:28 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	pwd(t_cmd *input)
{
	char	*now_path;

	now_path = get_now_path();
	if (errno)
	{
		ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		errno = 0;
		return ;
	}
	ft_putstr_fd(now_path, input->fd_out);
	ft_putstr_fd("\n", input->fd_out);
	free(now_path);
}
