/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:06:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/05 23:38:08 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_char_is_equal(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] == ' ')
		i++;
	if (s[i] == '=')
		return (1);
	return (0);
}

int	forbidden_char_is_exist_in_envp(const char *s)
{
	size_t	i;

	if (first_char_is_equal(s))
		return (1);
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		if (!is_snakecase(s[i], i))
			return (1);
		++i;
	}
	return (0);
}

int	is_exist_env(t_envp *envp, const char *new_env)
{
	t_envp	*p;
	size_t	i;

	p = envp;
	while (p != NULL)
	{
		i = 0;
		while (new_env[i] != '\0' && p->content[i] != '\0')
		{
			if (new_env[i] == '=' || p->content[i] == '='
				|| (new_env[i] != p->content[i]))
				break ;
			++i;
		}
		if (new_env[i] == '=' && p->content[i] == '=')
			return (1);
		else if (new_env[i] == '=' && p->content[i] == '\0')
			return (1);
		else if (new_env[i] == '\0' && p->content[i] == '\0')
			return (1);
		else if (new_env[i] == '\0' && p->content[i] == '=')
			return (2);
		p = p->next;
	}
	return (0);
}

int	get_max_rank(t_envp *envp)
{
	t_envp	*p;
	int		max_rank;

	p = envp;
	max_rank = -1;
	while (p != NULL)
	{
		if (p->rank > max_rank)
			max_rank = p->rank;
		p = p->next;
	}
	return (max_rank);
}
