/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refact_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:04:42 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/08 21:05:07 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	do_refact(t_list **now, t_list **top)
{
	if ((*now)->prev == NULL)
	{
		*now = (*now)->next;
		lstdel_head(top);
	}
	else if ((*now)->next == NULL)
	{
		*now = (*now)->prev;
		lstdel_tail(*now);
	}
	else
	{
		*now = (*now)->next;
		lstdel_mid(*now);
	}
}

void	refact_token(t_list **top)
{
	t_list	*now;
	t_list	*del;

	now = *top;
	while (now != NULL)
	{
		if (now->content == NULL || ft_strncmp(now->content, "\0", 1) == 0)
			do_refact(&now, top);
		else
			now = now->next;
	}
}
