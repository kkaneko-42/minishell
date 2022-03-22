/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 00:16:18 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/23 00:16:31 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_xmalloc(size_t size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
	{
		ft_putstr_fd(MALLOC_ERR, 2);
		exit(1);
	}
	return (res);
}
