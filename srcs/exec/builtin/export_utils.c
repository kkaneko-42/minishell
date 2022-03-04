/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:06:46 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/04 12:13:20 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	first_char_is_equal(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] == ' ')
		i++;
	if (s[i] == '=')
		return (1);
	return (0);
}
/* 
int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0);
		}
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
 */
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

/* 
//debug
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	t_envp	*envp_list;
	char	now_path[512];

	res = parser(av[1]);
	envp_list = get_envp_list(envp);
	for (t_cmd *now = res; now != NULL; now = now->next)
	{
		printf("cmd name:@%s@\n", now->name);
		printf("args:\n");
		for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
			printf("@%s@\n", arg_now->content);
	}
	exec(res, envp_list);
	//system("export");
	print_envp(envp_list);
	system("leaks -q a.out");
	return (0);
} */