/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:34:17 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/04 11:40:33 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var(t_list *token)
{
	t_list	*now_token;

	now_token = token;
	while (now_token != NULL)
	{
		if (now_token->content[0] != )
		now_token = now_token->next;
	}
}

