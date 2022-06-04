/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:11:38 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/04 12:22:00 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_null(char *s1, char *s2);

int	ft_envcmp(char *s1, char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (handle_null(s1, s2));
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		else if (*s1 == '=' || *s2 == '=')
			break ;
		s1++;
		s2++;
	}
	if (*s1 == '=' && *s2 != '=')
		return (-1);
	else if (*s1 != '=' && *s2 == '=')
		return (1);
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

static int	handle_null(char *s1, char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 != NULL && s2 == NULL)
		return (s1[0]);
	else if (s1 == NULL && s2 != NULL)
		return (s2[0]);
	return (0);
}
