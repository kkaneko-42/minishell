/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:48:33 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/23 00:38:57 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd(char **s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == 0)
		return (NULL);
	if (*s1 == NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL)
		return (ft_strdup(*s1));
	s1_len = ft_strlen(*s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == 0)
		return (NULL);
	ft_memmove(str, *s1, s1_len);
	ft_memmove(&str[s1_len], s2, s2_len);
	str[s1_len + s2_len] = '\0';
	free(*s1);
	*s1 = NULL;
	return (str);
}
/*
int main()
{
	char *s1 = ft_strdup("hello");
	char *s2 = ft_strdup("world");
	char *str;

	str = ft_stradd(&s1, s2);
	printf("res:%s\n", str);
	str = ft_stradd(&str, s2);
	printf("res:%s\n", str);
	str = ft_stradd(&str, s2);
	printf("res:%s\n", str);
	str = ft_stradd(&str, s2);
	printf("res:%s\n", str);
	str = ft_stradd(&str, s2);
	printf("res:%s\n", str);

	free(str);
	free(s2);
	return (0);
}
*/