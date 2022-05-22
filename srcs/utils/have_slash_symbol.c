/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_slash_symbol.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:29:12 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/05/22 18:11:09 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_slash_symbol(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{	
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
