/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 18:50:11 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/17 18:51:12 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_token(const t_list *token)
{
	if (check_metachar_target(token)
		|| check_nb_quotes(token))
	{
		ft_putstr_fd(PARSE_ERR, STDERR_FILENO);
		return (1);
	}
	return (0);
}
