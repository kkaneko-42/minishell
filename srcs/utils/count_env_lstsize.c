/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_env_lstsize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:54:45 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/23 22:55:32 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_env_lstsize(t_envp *env_list)
{
	int		res;
	t_envp	*now;

	now = env_list;
	res = 0;
	while (now != NULL)
	{
		++res;
		now = now->next;
	}
	return (res);
}
