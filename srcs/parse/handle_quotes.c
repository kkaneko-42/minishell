/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:32:35 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/11 21:50:47 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	cpy_in_quotes(
					char **dst, char *src, const char quote_type);

//give a ref of str as an argument
void	remove_quotes(char **token)
{
	char	*res;
	size_t	i;

	res = NULL;
	i = 0;
	while (42)
	{
		if ((*token)[i] == '\'' || (*token)[i] == '\"')
			i += cpy_in_quotes(&res, &((*token)[i]), (*token)[i]) + 1;
		else
			res = ft_stradd_char(&res, (*token)[i]);
		if ((*token)[i] == 0x00)
			break;
		else
			++i;
	}
	free(*token);
	*token = res;
}

static size_t	cpy_in_quotes(char **dst, char *src, const char quote_type)
{
	size_t	cnt_copy;

	src += 1;
	cnt_copy = 0;
	while (*src != quote_type && *src != 0x00)
	{
		*dst = ft_stradd_char(dst, *src);
		++src;
		++cnt_copy;
	}
	return (cnt_copy);
}
