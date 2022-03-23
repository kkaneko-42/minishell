/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:47:26 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 18:19:50 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	echo(t_cmd *input)
{
	t_list	*p_args;
	int		need_new_line;

	p_args = input->args;
	need_new_line = 1;
	if (p_args != NULL && ft_strncmp(p_args->content, "-n", 3) == 0)
	{
		need_new_line = 0;
		p_args = p_args->next;
	}
	while (p_args != NULL)
	{
		ft_putstr_fd(p_args->content, input->fd_out);
		p_args = p_args->next;
		if (p_args != NULL)
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