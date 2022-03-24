/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 18:57:24 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/02/22 23:36:39 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
/*
#include<string.h>
#include<stdio.h>

int main(){
	char *s = "12345";
	printf("%lu %lu\n", ft_strlen(s), strlen(s));
	char *st = "123456789";
	printf("%lu %lu\n", ft_strlen(st), strlen(st));
	char *str = "";
	printf("%lu %lu\n", ft_strlen(str), strlen(str));
}
*/