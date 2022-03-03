/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:34:17 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/02 23:51:34 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_from_name(t_list *token, t_envp *env);
static void	expand_from_args(t_list *token, t_envp *env);

void	expand_var(t_cmd *token, t_envp *env)
{
	t_list	*now_token;

	now_token = token;
	while (now_cmd != NULL)
	{
		expand_from_name(now_cmd, env);
		expand_from_args(now_cmd, env);
		now_cmd = now_cmd->next;
	}
}

