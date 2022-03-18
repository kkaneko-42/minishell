/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:47:26 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/18 16:24:23 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo(t_cmd *input)
{
	int		argc;
	t_list	*p;
	int		need_new_line;

	argc = ft_lstsize(input->args);
	p = input->args;
	need_new_line = 1;
	if (p != NULL && ft_strncmp(p->content, "-n", 3) == 0)
	{
		need_new_line = 0;
		p = p->next;
	}
	while (p != NULL)
	{
		ft_putstr_fd(p->content, input->fd_out);
		p = p->next;
		if (p != NULL)
			ft_putstr_fd(" ", input->fd_out);
	}
	if (need_new_line)
		ft_putstr_fd("\n", input->fd_out);
}
/* 
//debug
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	t_envp	*envp_list;

	res = parser(av[1]);
	envp_list = get_envp_list(envp);
	exec(res, envp_list);
	return (0);
} */