/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_nb_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 21:07:43 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 23:47:41 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_quotes(const char *str, size_t *nb_double, size_t *nb_single);
static int	quotation_is_quoted(size_t nb_another_quotes);
static int	is_odd(size_t n);

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
		count_quotes(now->content, &nb_double_quotes, &nb_single_quotes);
		if (is_odd(nb_double_quotes) || is_odd(nb_single_quotes))
			return (1);
		now = now->next;
	}
	return (0);
}

static void	count_quotes(const char *str, size_t *nb_double, size_t *nb_single)
{
	size_t	i;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '\"' && !quotation_is_quoted(*nb_single))
			++(*nb_double);
		else if (str[i] == '\'' && !quotation_is_quoted(*nb_double))
			++(*nb_single);
		++i;
	}
}

//Whether the quotation is surrounded by another one
//(eg. Is double quote(") surrounded by single quote(')?)
static int	quotation_is_quoted(size_t nb_another_quotes)
{
	if (is_odd(nb_another_quotes))
		return (1);
	else
		return (0);
}

static int	is_odd(size_t n)
{
	if (n % 2 == 1)
		return (1);
	else
		return (0);
}
