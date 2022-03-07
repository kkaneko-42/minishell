/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:32:16 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/07 16:46:36 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

//res init: ft_stradd_char returns NULL if first argument is null.
//By initializing as \0, we are able to concatnate string whenever.
size_t	ft_strreplace(
			char **str, const char *replace, size_t start, size_t end)
{
	size_t	i;
	char	*res;

	res = ft_strdup("\0");
	i = 0;
	while ((*str)[i] != 0x00)
	{
		if (i == start)
		{
			res = ft_stradd(&res, replace);
			i = end;
		}
		else
			res = ft_stradd_char(&res, (*str)[i]);
		++i;
	}
	free(*str);
	*str = res;
	return (start + ft_strlen(replace) - 1);
}
/*
//debug
#include <stdlib.h>
#include <stdio.h>
int main(int ac, char **av)
{
	char	*src = ft_strdup("01$HOGE456789"); // => 0123456789
	char	*replace = "23";
	size_t	start = 2;
	size_t	end = 6;

	printf("src:%s\n", src);
	ft_strreplace(&src, replace, start, end);
	printf("res:%s\n", src);
	free(src);
	return (0);
}
*/
