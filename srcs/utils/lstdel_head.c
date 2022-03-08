/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdel_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:44:30 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/08 19:06:52 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_content(char *content)
{
	free(content);
}

void	lstdel_head(t_list **top)
{
	t_list	*del;

	del = *top;
	del->next->prev = NULL;
	*top = del->next;
	ft_lstdelone(del, free_content);
}
