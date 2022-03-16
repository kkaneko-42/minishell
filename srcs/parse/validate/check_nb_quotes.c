/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:07:43 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/16 00:59:07 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_quotes(const char *str, const char quote_type);
static int		is_odd(size_t n);

int	check_nb_quotes(const t_list *tokens)
{
	size_t	nb_double_quotes;
	size_t	nb_single_quotes;
	t_list	*now;

	nb_double_quotes = 0;
	nb_single_quotes = 0;
	now = (t_list *)tokens;
	while (now != NULL)
	{
		nb_double_quotes = count_quotes(now->content, '\"');
		nb_single_quotes = count_quotes(now->content, '\'');
		if (is_odd(nb_double_quotes) || is_odd(nb_single_quotes))
			return (1);
		now = now->next;
	}
	return (0);
}

static size_t	count_quotes(const char *str, const char quote_type)
{
	size_t	i;
	size_t	res;

	res = 0;
	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == quote_type)
			++res;
		++i;
	}
	return (res);
}

static int	is_odd(size_t n)
{
	if (n % 2 == 1)
		return (1);
	else
		return (0);
}
