/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:26:57 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/02/22 23:38:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	if (dst > src)
	{
		while (i < len)
		{
			((char *)dst)[len - 1 - i] = ((char *)src)[len - 1 - i];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*p;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
		i++;
	p = (char *)ft_xmalloc(sizeof(char) * (i + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	if (s1 == NULL)
		return (ft_strdup((char *)s2));
	if (s2 == NULL)
		return (ft_strdup((char *)s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_xmalloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	ft_memmove(str, s1, s1_len);
	ft_memmove(&str[s1_len], s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	while (i < s_len + 1)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
*/