/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:32:35 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/16 15:07:59 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	cpy_in_quotes(
					char **dst, char *src, const char quote_type);

void	remove_quotes_from_cmds(t_cmd *top)
{
	t_cmd	*now_cmd;
	t_list	*now_arg;

	now_cmd = top;
	while (now_cmd != NULL)
	{
		remove_quotes(&(now_cmd->name));
		now_arg = now_cmd->args;
		while (now_arg != NULL)
		{
			remove_quotes(&(now_arg->content));
			now_arg = now_arg->next;
		}
		now_cmd = now_cmd->next;
	}
}

//give a ref of str as an argument
void	remove_quotes(char **str)
{
	char	*res;
	size_t	i;

	res = NULL;
	i = 0;
	while (42)
	{
		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			i += cpy_in_quotes(&res, &((*str)[i]), (*str)[i]) + 1;
		else
			res = ft_stradd_char(&res, (*str)[i]);
		if ((*str)[i] == 0x00)
			break ;
		else
			++i;
	}
	free(*str);
	*str = res;
}

static size_t	cpy_in_quotes(char **dst, char *src, const char quote_type)
{
	size_t	cnt_copy;

	src += 1;
	cnt_copy = 0;
	while (*src != quote_type && *src != 0x00)
	{
		*dst = ft_stradd_char(dst, *src);
		++src;
		++cnt_copy;
	}
	return (cnt_copy);
}
