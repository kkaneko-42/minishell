/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:30:28 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 17:11:15 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_env(t_cmd *input, t_envp *envp);
static int	have_equal(const char *s);

int	env(t_cmd *input, t_envp *envp)
{
	int	argc;

	argc = ft_lstsize(input->args);
	if (argc == 0)
		print_env(input, envp);
	else
		return (too_many_args_err("env"));
	return (CMD_SUCCESS);
}

static void	print_env(t_cmd *input, t_envp *envp)
{
	t_envp	*p;

	p = envp;
	while (p != NULL)
	{
		if (have_equal(p->content)
			&& !forbidden_char_is_exist_in_envp(p->content))
			ft_putstr_fd(p->content, input->fd_out);
		ft_putstr_fd("\n", input->fd_out);
		p = p->next;
	}
}

static int	have_equal(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		++i;
	}
	return (0);
}
