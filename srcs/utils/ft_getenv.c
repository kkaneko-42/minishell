/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 23:08:09 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/06 23:08:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_strs(char **strs);
static char	*get_env_value(char *env);
static int	is_exist(const char *name, char *env);

char	*ft_getenv(const char *name, t_envp *env_list)
{
	const size_t	cmp_len = ft_strlen(name) + 1;
	t_envp			*now_env;

	now_env = env_list;
	while (now_env != NULL)
	{
		if (is_exist(name, now_env->content))
			return (get_env_value(now_env->content));
		now_env = now_env->next;
	}
	return (NULL);
}

static void	free_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		strs[i] = NULL;
		++i;
	}
	free(strs);
}

static char	*get_env_value(char *env)
{
	char	*res;

	res = ft_strchr(env, '=');
	if (res == NOT_FOUND)
		return (ft_strchr(env, '\0'));
	else
		return (res + 1);
}

static int	is_exist(const char *name, char *env)
{
	const size_t	cmp_len = ft_strlen(name) + 1;
	char			**name_and_value;
	int				res;

	name_and_value = ft_split(env, '=');
	if (ft_strncmp(name_and_value[0], name, cmp_len) == 0)
		res = 1;
	else
		res = 0;
	free_strs(name_and_value);
	return (res);
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

	//printf("res:@%s@\n", ft_getenv(av[1], env));
	for (t_envp *now = env; now != NULL; now = now->next)
	{
		printf("%s\n", now->content);
	}
	return (0);
}
*/
