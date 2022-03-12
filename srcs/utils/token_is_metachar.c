/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_is_metachar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 03:02:04 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/13 03:02:29 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*get_metachar_list(void);

int	token_is_metachar(const t_list *token)
{
	t_list	*lst_metachar;
	t_list	*now;

	lst_metachar = get_metachar_list();
	now = lst_metachar;
	while (now != NULL)
	{
		if (ft_strncmp(token->content, now->content, ft_strlen(now->content)) == 0)
			return (1);
		now = now->next;
	}
	ft_lstclear(&lst_metachar, free_content);
	return (0);
}

static t_list	*get_metachar_list(void)
{
	t_list	*res;

	res = NULL;
	ft_lstadd_back(&res, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&res, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&res, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&res, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&res, ft_lstnew(ft_strdup("|")));
	return (res);
}
