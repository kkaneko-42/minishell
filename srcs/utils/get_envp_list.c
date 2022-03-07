/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:41:55 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/07 17:42:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envp	*get_envp_list(char **envp)
{
	t_envp	*envp_list;
	size_t	i;

	envp_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		addback_envp_list(&envp_list, envp[i]);
		++i;
	}
	addback_envp_list(&envp_list, "?=0  ");
	ft_getenv("?", envp_list)[1] = '\0';
	return (envp_list);
}
