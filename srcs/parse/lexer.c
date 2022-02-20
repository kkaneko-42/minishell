/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko </var/mail/kkaneko>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:21:59 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/20 15:27:32 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**split_cmd_arg(const char *input);

char	**lexer(const char *input)
{
	if (input == NULL)
		return (NULL);
}

static char	**split_cmd_arg(const char *input)
{
	size_t	i;

	i = 0;
	skip_whitespace(input, &i);
	while (input[i] != 0x00)
	{
	}
}
