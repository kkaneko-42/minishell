/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metachar_target.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 02:58:35 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/13 03:08:02 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_metachar_target(const t_list *token)
{
	t_list	*metachar_list;
	t_list	*now;

	now = token;
	while (now != NULL)
	{
		if (token_is_metachar(now))

		now = now->next;
	}
}
