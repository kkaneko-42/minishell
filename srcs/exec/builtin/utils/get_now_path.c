/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_now_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 00:04:43 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 19:53:56 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

char	*get_now_path(void)
{
	char	*now_path;
	int		first_loop;
	size_t	size;

	now_path = NULL;
	first_loop = 1;
	size = 1;
	errno = 0;
	while (errno == ERANGE || first_loop)
	{
		free(now_path);
		errno = 0;
		first_loop = 0;
		now_path = (char *)ft_xmalloc(sizeof(char) * (size + 1));
		getcwd(now_path, size);
		now_path[size] = '\0';
		++size;
	}
	if (errno)
	{
		free(now_path);
		now_path = NULL;
	}
	return (now_path);
}
