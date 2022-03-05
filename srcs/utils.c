/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:55:41 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/06 00:25:04 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_result(char *env)
{
	size_t	i;

	i = 0;
	while (env[i] != '=')
		++i;
	return (&env[i + 1]);
}

static int	is_exist(const char *name, char *env)
{
	const size_t	name_len = ft_strlen(name);
	size_t			i;

	i = 0;
	while (name[i] != 0x00 && env[i] != 0x00)
		++i;
	if (name[i] == 0x00 && env[i] == '=')
		return (1);
	else
		return (0);
}

char	*ft_getenv(const char *name, t_envp *env_list)
{
	const size_t	cmp_len = ft_strlen(name) + 1;
	t_envp			*now_env;

	now_env = env_list;
	while (now_env != NULL)
	{
		if (is_exist(name, now_env->content))
			return (get_result(now_env->content));
		now_env = now_env->next;
	}
	return (NULL);
}
/*
//debug
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
	return (envp_list);
}

int main(int ac, char **av, char **envp)
{
	t_envp	*env = get_envp_list(envp);

	printf("top of list:@%s@\n", env->content);
	printf("res:@%s@\n", ft_getenv(av[1], env));
	return (0);
}
*/
