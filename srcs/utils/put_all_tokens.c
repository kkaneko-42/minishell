/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_all_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:51:59 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 01:25:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_all_tokens(t_list *tokens)
{
	t_list	*now;

	now = tokens;
	while (now != NULL)
	{
		printf("===============================\n");
		printf("content:%s\n", now->content);
		printf("prev:%p\n", now->prev);
		printf("now:%p\n", now);
		printf("next:%p\n", now->next);
		now = now->next;
	}
}
