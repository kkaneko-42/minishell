/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:36:42 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 22:53:58 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	t_cmd_size(t_cmd *input)
{
	int		i;
	t_cmd	*now;

	i = 0;
	now = input;
	while (now != NULL)
	{
		++i;
		now = now->next;
	}
	return (i);
}