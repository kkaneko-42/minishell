/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_snakecase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:08:50 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/06 23:12:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_snakecase(char c, size_t i)
{
	if (i == 0 && ft_isdigit(c))
		return (0);
	else if (ft_isalnum(c) || c == '_')
		return (1);
	else
		return (0);
}
