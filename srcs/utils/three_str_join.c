/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_str_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:40:57 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/23 22:41:13 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*three_strjoin(char *s1, char *s2, char *s3)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	str = (char *)ft_xmalloc(sizeof(char) * (s1_len + s2_len + s3_len + 1));
	ft_memmove(str, s1, s1_len);
	ft_memmove(&str[s1_len], s2, s2_len);
	ft_memmove(&str[s1_len + s2_len], s3, s3_len);
	str[s1_len + s2_len + s3_len] = '\0';
	return (str);
}
