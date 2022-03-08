/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:21:59 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/08 23:38:27 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	get_str_in_quote(
		const char *input, t_list *dst, size_t *input_i);
static void	get_metachar(
		const char *input, t_list **now, size_t *input_i);
static void	skip_whitespace(
		const char *input, t_list **now, size_t *input_i);
static void	metachar_to_list(
		char *metachar, t_list **now, size_t *input_i);

t_list	*lexer(const char *input)
{
	t_list	*res;
	t_list	*now;
	size_t	i;

	if (input == NULL)
		return (NULL);
	res = ft_lstnew(ft_strdup("\0"));
	now = res;
	i = 0;
	while (input[i] != 0x00)
	{
		if (input[i] == ' ')
			skip_whitespace(input, &now, &i);
		else if (input[i] == '\"' || input[i] == '\'')
			get_str_in_quote(input, now, &i);
		else if (ft_strchr("><|", input[i]) != NOT_FOUND)
			get_metachar(input, &now, &i);
		else
			now->content = ft_stradd_char(&(now->content), input[i++]);
	}
	return (res);
}

static void	skip_whitespace(
		const char *input, t_list **now, size_t *input_i)
{
	const int	fg_no_content = !(ft_strlen((*now)->content));

	while (input[*input_i] == ' ')
		++(*input_i);
	if (!fg_no_content && input[*input_i] != 0x00)
	{
		ft_lstadd_back(now, ft_lstnew(ft_strdup("\0")));
		*now = (*now)->next;
	}
}

static void	get_str_in_quote(
		const char *input, t_list *dst, size_t *input_i)
{
	const char		quote = input[*input_i];
	unsigned int	start_i;
	char			*src_str;

	start_i = (unsigned int)(*input_i);
	(*input_i) += 1;
	while (input[(*input_i)] != quote)
		++(*input_i);
	src_str = ft_substr(input, start_i, *input_i - (size_t)start_i + 2);
	(*input_i) += 1;
	dst->content = ft_stradd(&(dst->content), src_str);
}

static void	metachar_to_list(
		char *metachar, t_list **now, size_t *input_i)
{
	const int	fg_no_content = !(ft_strlen((*now)->content));

	if (fg_no_content)
	{
		(*now)->content = ft_stradd(&((*now)->content), metachar);
		ft_lstadd_back(now, ft_lstnew(ft_strdup("\0")));
		*now = (*now)->next;
	}
	else
	{
		ft_lstadd_back(now, ft_lstnew(ft_strdup(metachar)));
		ft_lstadd_back(now, ft_lstnew(ft_strdup("\0")));
		*now = (*now)->next->next;
	}
	*input_i += ft_strlen(metachar);
}

static void	get_metachar(
		const char *input, t_list **now, size_t *input_i)
{
	const char	now_c = input[*input_i];
	const char	next_c = input[*input_i + 1];

	if (now_c == '>' && next_c == '>')
		metachar_to_list(">>", now, input_i);
	else if (now_c == '>')
		metachar_to_list(">", now, input_i);
	else if (now_c == '<' && next_c == '<')
		metachar_to_list("<<", now, input_i);
	else if (now_c == '<')
		metachar_to_list("<", now, input_i);
	else if (now_c == '|')
		metachar_to_list("|", now, input_i);
}
/*
//debug
int	main(int ac, char **av)
{
	t_list	*res;
	char	*input = ft_strdup("cat \"<< end\"");

	printf("input:@%s@\n", input);
	res = lexer(input);
	for (int i = 0; res != NULL; res = res->next)
		printf("%s\n", res->content);
	return (0);
}
*/
