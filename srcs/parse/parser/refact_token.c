/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refact_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:04:42 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 17:59:06 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_empty_node(t_list **now, t_list **top)
{
	t_list	*now_after_refact;

	if ((*now)->prev == NULL)
	{
		*now = (*now)->next;
		lstdel_head(top);
	}
	else if ((*now)->next == NULL)
	{
		now_after_refact = (*now)->prev;
		lstdel_tail(*now);
		*now = now_after_refact;
	}
	else
	{
		now_after_refact = (*now)->next;
		lstdel_mid(*now);
		*now = now_after_refact;
	}
}

void	refact_token(t_list **top)
{
	t_list	*now;

	now = *top;
	while (now != NULL)
	{
		if (now->content == NULL || ft_strncmp(now->content, "\0", 1) == 0)
			del_empty_node(&now, top);
		else
			now = now->next;
	}
}
