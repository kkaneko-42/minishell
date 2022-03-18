/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:15:45 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 16:20:19 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_node(t_envp **env_node, void (*del)(char *));

void	free_envp_list(t_envp **env_list, void (*del)(char *))
{
	t_envp	*now_env;
	t_envp	*next_env;

	now_env = *env_list;
	while (now_env != NULL)
	{
		next_env = now_env->next;
		free_env_node(&now_env, del);
		now_env = next_env;
	}
}

static void	free_env_node(t_envp **env_node, void (*del)(char *))
{
	(*del)((*env_node)->content);
	free(*env_node);
	*env_node = NULL;
}
