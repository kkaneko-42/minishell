/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:19:05 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/06 17:54:23 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	try_expand(char *str, t_envp *env_list);
static char	*get_env_name(char *str);

void	expand_env(t_list *token, t_envp *env_list)
{
	t_list	*now_token;

	now_token = token;
	while (now_token != NULL)
	{
		if (now_token->content[0] != '\'')
			try_expand(now_token->content, env_list);
		now_token = now_token->next;
	}
}

static void	try_expand(char *str)
{
	size_t			i;
	char			*env_name;

	i = 0;
	while (str[i] != 0x00)
	{
		if (str[i] == '$')
		{
			env_name = get_env_name(&str[i]);
		}
		++i;
	}
}
