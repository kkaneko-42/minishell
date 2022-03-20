/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 01:32:16 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/21 01:02:00 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_envname_head_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0x00 && str[i] != '$')
		++i;
	return (i + 1);
}

size_t	get_envname_tail_index(char *str)
{
	size_t	start_i;
	size_t	now_i;

	start_i = get_envname_head_index(str);
	now_i = start_i;
	if (str[now_i] == '?')
		return (now_i);
	while (is_snakecase(str[now_i], now_i - start_i))
		++now_i;
	return (now_i - 1);
}

char	*get_env_name_from_token(char *str)
{
	size_t	head_i;
	size_t	tail_i;
	char	*res;

	head_i = get_envname_head_index(str);
	tail_i = get_envname_tail_index(str);
	res = ft_substr(str, head_i, tail_i - head_i + 1);
	return (res);
}
