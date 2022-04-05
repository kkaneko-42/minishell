/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 14:47:26 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/05 23:37:03 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_only_option_n(const char *content);

void	echo(t_cmd *input)
{
	t_list	*p_args;
	int		fg_new_line;

	p_args = input->args;
	fg_new_line = 1;
	while (p_args != NULL && is_only_option_n(p_args->content))
	{
		fg_new_line = 0;
		p_args = p_args->next;
	}
	while (p_args != NULL)
	{
		ft_putstr_fd(p_args->content, input->fd_out);
		p_args = p_args->next;
		if (p_args != NULL)
			ft_putstr_fd(" ", input->fd_out);
	}
	if (fg_new_line)
		ft_putstr_fd("\n", input->fd_out);
}

static int	is_only_option_n(const char *content)
{
	size_t	i;
	size_t	count_n;

	if (content[0] != '-')
		return (0);
	i = 0;
	count_n = 0;
	while (content[i] != '\0')
	{
		if (content[i] == 'n')
			++count_n;
		++i;
	}
	if (count_n == ft_strlen(content) - 1 && count_n != 0)
		return (1);
	return (0);
}
