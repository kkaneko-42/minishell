/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:25:50 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/04 18:03:31 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = (t_list *)ft_xmalloc(sizeof(t_list) * 1);
	new->content = content;
	new->next = 0;
	new->prev = 0;
	return (new);
}
/* 
int main()
{
	t_list *new;
	
	new = ft_lstnew("new");
	printf("now->content = %s\n", (char *)new->content);
	printf("now->next = %s\n", (char *)new->next);
}
 */