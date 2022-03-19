/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:06:30 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/20 00:01:18 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_empty(char *s);
static char	*get_now_path(void);

void	pwd(t_cmd *input)
{
	int		argc;
	char	*now_path;

	argc = ft_lstsize(input->args);
	if (argc >= 1 && !is_empty(input->args->content))
		ft_putendl_fd("pwd: too many arguments", STDERR_FILENO);
	else
	{
		now_path = get_now_path();
		ft_putstr_fd(now_path, input->fd_out);
		ft_putstr_fd("\n", input->fd_out);
	}
}

static int	is_empty(char *s)
{
	if (s[0] == '\0')
		return (1);
	return (0);
}

static char	*get_now_path(void)
{
	char	*now_path;
	int		first_roop;
	size_t	size;

	now_path = NULL;
	first_roop = 1;
	size = 0;
	errno = 0;
	while (errno != 0 || first_roop)
	{
		free(now_path);
		errno = 0;
		first_roop = 0;
		now_path = (char *)malloc(sizeof(char) * (size + 1));
		getcwd(now_path, size);
		now_path[size] = '\0';
		++size;
	}
	return (now_path);
}
