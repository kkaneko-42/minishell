/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metachar_target.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:58:35 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 16:34:50 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_no_target(t_list *metachar_node);

int	check_metachar_target(const t_list *token)
{
	t_list	*now;

	now = (t_list *)token;
	while (now != NULL)
	{
		if (is_metachar(now->content) && has_no_target(now))
			return (1);
		now = now->next;
	}
	return (0);
}

static int	has_no_target(t_list *metachar_node)
{
	char	*next_content;
	int		res;

	res = 0;
	if (metachar_node->next == NULL)
		return (1);
	next_content = ft_strdup(metachar_node->next->content);
	if (ft_strlen(next_content) == 0 || is_metachar(next_content))
		res = 1;
	free(next_content);
	return (res);
}
