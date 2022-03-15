/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addback_envp_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:42:30 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/11 19:41:59 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	addback_envp_list(t_envp **envp_list, char *s)
{
	t_envp	*new_envp;
	t_envp	*p;

	new_envp = (t_envp *)ft_xmalloc(sizeof(t_envp) * 1);
	new_envp->content = ft_strdup(s);
	new_envp->rank = 0;
	if (new_envp->content == NULL)
		return (0);
	if (*envp_list == NULL)
	{
		new_envp->next = NULL;
		new_envp->prev = NULL;
		*envp_list = new_envp;
		return (1);
	}
	p = *envp_list;
	while (p->next != NULL)
		p = p->next;
	p->next = new_envp;
	new_envp->next = NULL;
	new_envp->prev = p;
	return (1);
}
