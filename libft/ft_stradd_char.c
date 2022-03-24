/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 00:05:16 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/11 21:20:59 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd_char(char **str, const char c)
{
	size_t	str_len;
	char	*res;

	if (str == NULL)
		return (NULL);
	str_len = ft_strlen(*str);
	res = (char *)ft_xmalloc(sizeof(char) * (str_len + 2));
	ft_memmove(res, *str, sizeof(char) * str_len);
	res[str_len] = c;
	res[str_len + 1] = 0x00;
	free(*str);
	*str = NULL;
	return (res);
}
