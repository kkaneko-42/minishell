/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:19:05 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/05 14:41:20 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	try_expand(char *str);
static char	*get_env_name_from_dollar(char *str);

void	expand_env(t_list *token)
{
	t_list	*now_token;

	now_token = token;
	while (now_token != NULL)
	{
		if (now_token->content[0] != '\'')
			try_expand(now_token->content);
		now_token = now_token->next;
	}
}

static void	try_expand(char *str)
{
	size_t			i;
	size_t			env_start_i;
	size_t			env_end_i;
	char			*env_name;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '$')
			env_name = get_env_name_from_dollar(&str[i]);
		++i;
	}
}

//str[0] is $
static char	*get_env_name_from_dollar(char *str)
{
	char	*env_name;
	size_t	env_start_i;
	size_t	env_len;

	env_start_i = 1;
	env_len = 0;
	//may need to support other space(tab for example)
	while (str[env_len + 1] != ' ')
}
