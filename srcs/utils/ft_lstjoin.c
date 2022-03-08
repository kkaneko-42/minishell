/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:34:42 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/08 21:38:18 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lstjoin(t_list **lst1, t_list *lst2)
{
	t_list	*eol;

	if (*lst1 == NULL)
		*lst1 = lst2;
	else
	{
		eol = ft_lstlast(*lst1);
		eol->next = lst2;
	}
}
