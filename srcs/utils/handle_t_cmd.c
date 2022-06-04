/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_t_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:10:29 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/04 12:25:35 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_metachar(t_cmd *cmd, t_list **token);
static void	get_cmd_name(t_cmd *cmd, t_list **token);

void	get_cmd_info(t_cmd *cmd, t_list **token)
{
	parse_metachar(cmd, token);
	while ((*token) != NULL)
	{
		if (ft_strncmp((*token)->content, "|", 2) == 0)
		{
			(*token) = (*token)->next;
			break ;
		}
		get_cmd_name(cmd, token);
		get_cmd_args(cmd, token);
		parse_metachar(cmd, token);
	}
}

static void	get_cmd_name(t_cmd *cmd, t_list **token)
{
	cmd->name = ft_strdup((*token)->content);
	(*token) = (*token)->next;
}

void	get_cmd_args(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL && !is_metachar((*token)->content))
	{
		ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup((*token)->content)));
		*token = (*token)->next;
	}
}

t_cmd	*cmd_new(char *name)
{
	t_cmd	*res;

	res = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->name = name;
	res->fd_out = 1;
	return (res);
}

void	cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*now;

	if (*lst == NULL)
		*lst = new;
	else
	{
		now = *lst;
		while (now->next != NULL)
			now = now->next;
		now->next = new;
		new->prev = now;
	}
}
