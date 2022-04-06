/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:06:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/05 23:38:27 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_node(t_envp **envp, t_envp **p_envp);
static void	delete_first_node(t_envp **envp, t_envp **p_envp);
static void	delete_last_node(t_envp **p_envp);
static void	delete_between_node(t_envp **p_envp);

void	delete_env(t_envp **envp, char *old_env)
{
	t_envp	*p_envp;
	size_t	i;

	p_envp = *envp;
	while (p_envp != NULL)
	{
		i = 0;
		while (old_env[i] != '\0' && p_envp->content[i] != '\0')
		{
			if ((old_env[i] == '=' || p_envp->content[i] == '=')
				|| (old_env[i] != p_envp->content[i]))
				break ;
			++i;
		}
		if ((old_env[i] == '=' && p_envp->content[i] == '=')
			|| (old_env[i] == '\0' && p_envp->content[i] == '=')
			|| (old_env[i] == '=' && p_envp->content[i] == '\0')
			|| (old_env[i] == '\0' && p_envp->content[i] == '\0'))
		{
			delete_node(envp, &p_envp);
			break ;
		}
		p_envp = p_envp->next;
	}
}

static void	delete_node(t_envp **envp, t_envp **p_envp)
{
	if ((*p_envp)->prev == NULL)
		delete_first_node(envp, p_envp);
	else if ((*p_envp)->next == NULL)
		delete_last_node(p_envp);
	else
		delete_between_node(p_envp);
}

static void	delete_first_node(t_envp **envp, t_envp **p_envp)
{
	t_envp	*tmp;

	if ((*p_envp)->next == NULL)
	{
		free((*p_envp)->content);
		(*p_envp)->content = NULL;
		free(*p_envp);
		*p_envp = NULL;
	}
	else
	{
		tmp = *p_envp;
		(*p_envp)->next->prev = NULL;
		*envp = (*p_envp)->next;
		*p_envp = (*p_envp)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

static void	delete_last_node(t_envp **p_envp)
{
	(*p_envp)->prev->next = NULL;
	free((*p_envp)->content);
	(*p_envp)->content = NULL;
	free(*p_envp);
	*p_envp = NULL;
}

static void	delete_between_node(t_envp **p_envp)
{
	t_envp	*tmp;

	tmp = *p_envp;
	(*p_envp)->prev->next = (*p_envp)->next;
	(*p_envp)->next->prev = (*p_envp)->prev;
	(*p_envp) = (*p_envp)->next;
	free((tmp)->content);
	(tmp)->content = NULL;
	free(tmp);
	tmp = NULL;
}
