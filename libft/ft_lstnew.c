/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 21:25:50 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/04 15:57:53 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*new;

	new = (t_list *)ft_xmalloc(sizeof(t_list) * 1);
	if (new == 0)
		return (NULL);
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