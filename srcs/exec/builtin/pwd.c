/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:06:30 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/15 13:29:39 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_empty(char *s);

void	pwd(t_cmd *input)
{
	int		argc;
	char	now_path[512];

	argc = ft_lstsize(input->args);
	if (argc >= 1 && !is_empty(input->args->content))
		printf("pwd: too many arguments\n");
	else
	{
		getcwd(now_path, 512);
		ft_putstr_fd(now_path, input->fd_out);
		ft_putstr_fd("\n", input->fd_out);
	}
}

static int	is_empty(char *s)
{
	if (s[0] == 0x00)
		return (1);
	return (0);
}
