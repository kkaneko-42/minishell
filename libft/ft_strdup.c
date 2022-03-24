/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 21:23:39 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/02/22 23:35:53 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/* 
int	main(void)
{
	char	*a1 = "12345";
	char	*b1;
	char	*a2 = "12345";
	char	*b2;
	
	b1 = strdup(a1);
	printf("honke:a = %s\n", a1);
	printf("honke:b = %s\n", b1);
	
	b2 = ft_strdup(a2);
	printf("zisaku:a = %s\n", a1);
	printf("zisaku:b = %s\n", b1);
	
}
 */