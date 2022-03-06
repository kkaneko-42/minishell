/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:32:16 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/07 00:31:36 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"

static void	do_replace(char **res, const char *replace);

//res init: ft_stradd_char returns NULL if first argument is null.
//By initializing as \0, we are able to concatnate string whenever.
char	*ft_strreplace(
			const char *str, const char *replace, size_t start, size_t end)
{
	size_t	i;
	char	*res;

	res = ft_strdup("\0");
	i = 0;
	while (str[i] != 0x00)
	{
		if (i == start)
		{
			do_replace(&res, replace); //do_replace
			i = end;
		}
		else
			res = ft_stradd_char(&res, str[i]);
		++i;
	}
	return (res);
}

static void	do_replace(char **res, const char *replace)
{
	size_t	replace_i;

	replace_i = 0;
	while (replace[replace_i] != 0x00)
	{
		*res = ft_stradd_char(res, replace[replace_i]);
		++replace_i;
	}
}
/*
//debug
#include <stdlib.h>
#include <stdio.h>
int main(int ac, char **av)
{
	char	*src = "0123$HOGE6789";
	char	*replace = "45";
	size_t	start = 4;
	size_t	end = 8;

	printf("src len:%zu\n", ft_strlen(src));
	printf("end:%zu\n", end);
	printf("res:%s\n", ft_strreplace(src, replace, start, end));
	return (0);
}
*/
