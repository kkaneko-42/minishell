/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko </var/mail/kkaneko>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:21:59 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/20 19:33:24 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_str_in_quote(
		const char *input, t_list *dst, size_t *input_i);
static void	get_metachar(
		const char *input, t_list **dst, size_t *input_i);
static void	skip_whitespace(
		const char *input, size_t *input_i);

t_list	*lexer(const char *input)
{
	t_list	*res;
	t_list	*now;
	size_t	i;

	if (input == NULL)
		return (NULL);
	res = ft_lstnew(ft_strdup(input));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (input[i] != 0x00)
	{
		if (input[i] == ' ')
			skip_whitespace(input, &i);
		if (input[i] == '"' || input[i] == ''')
			get_str_in_quote(input, res, now, &i);
		else if (ft_strchr(META_CHAR, input[i]) != NOT_FOUND)
			get_metachar(input, res, &now, &i);
		else
			res[i] = input[i++];
	}
	return (res);
}

static void	skip_whitespace(
		const char *input, size_t *input_i)
{
	while (input[input_i] != ' ')
		++(*input_i);
}

static void	get_str_in_quote(
		const char *input, t_list *dst, size_t *input_i)
{
	const char		quote = input[input_i];
	unsigned int	start_i;
	size_t			dst_len;

	start_i = *input_i;
	*input_i += 1;
	dst_len = 0;
	while (input[*input_i] != quote)
	{
		++dst_len;
		++(*input_i);
	}
	*(dst)->content = ft_substr(input, start_i, dst_len);
}
