/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfirst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:44:19 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/17 17:45:44 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfirst(t_list *lst)
{
	t_list	*now_lst;

	now_lst = lst;
	if (now_lst == NULL)
		return (NULL);
	while (now_lst->prev != NULL)
		now_lst = now_lst->prev;
	return (now_lst);
}
