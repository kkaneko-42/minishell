/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdel_tail.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 18:49:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/08 19:07:33 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_content(char *content)
{
	free(content);
}

void	lstdel_tail(t_list *lst)
{
	t_list	*del;

	del = ft_lstlast(lst);
	del->prev->next = NULL;
	ft_lstdelone(del, free_content);
}