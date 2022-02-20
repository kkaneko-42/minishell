/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko </var/mail/kkaneko>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:21:59 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/20 17:14:07 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_str_until_quote_ended(
		const char *input, char **res, size_t *col, size_t *row);
static void	metachar_to_res(
		const char *input, char **res, size_t *col, size_t *row);
static void	skip_whitespace(
		const char *input, size_t *checking_i);

t_list	*lexer(const char *input)
{
	size_t	i;
	size_t	j;
	t_list	*res;

	if (input == NULL)
		return (NULL);
	res = NULL;
	i = 0;
	j = 0;
	while (input[i] != 0x00)
	{
		skip_whitespace(input, &i);
		if (input[i] == '"' || input[i] == ''')
			get_str_until_quote_ended(input, res, &i, &j);
		else if (ft_strchr(META_CHAR, input[i]) != NOT_FOUND)
			metachar_to_res(input, res, &i, &j);
		else
			res[i] = input[i++];
	}
	return (res);
}

static void	skip_whitespace(
		const char *input, size_t *checking_i)
{
	while (input[checking_i] != ' ')
		++(*checking_i);
}

static void	get_str_until_quote_ended(
		const char *input, char **res, size_t *col, size_t *row)
{
	size_t		input_i;
	size_t		res_i;
	const char	quote_start = input[*col];

	i = *col;
	while (input[i] != 0x00 && input[i] != quote_start)
	{
	}
}
