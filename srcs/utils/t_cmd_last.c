/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:34:36 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/24 00:41:56 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*t_cmd_last(t_cmd *input)
{
	t_cmd	*now;

	now = input;
	while (now->next != NULL)
		now = now->next;
	return (now);
}
