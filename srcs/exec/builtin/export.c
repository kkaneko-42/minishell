/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/06 16:10:56 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	sort_envp(t_envp *envp);
static void	print_envp(t_envp *envp);
static void	print_envp_content(char *content);

void	export(t_cmd *input, t_envp *envp)
{
	int		argc;
	t_list	*p_args;

	argc = ft_lstsize(input->args);
	if (argc == 0)
		print_envp(envp);
	else
	{
		p_args = input->args;
		while (p_args != NULL)
		{
			if (forbidden_char_is_exist_in_envp(p_args->content))
				printf("minishell: export: `%s': not a valid identifier\n",
					p_args->content);
			else if (is_exist_env(envp, p_args->content) == 1)
			{
				delete_env_export(&envp, p_args->content);
				addback_envp_list(&envp, p_args->content);
			}
			else if (is_exist_env(envp, p_args->content) != 2)
			{
				if (!addback_envp_list(&envp, p_args->content)) //malloc err
					printf("exit?");//exit?
			}
			p_args = p_args->next;
		}
	}
}

static void	sort_envp(t_envp *envp)
{
	t_envp	*p1;
	t_envp	*p2;

	p1 = envp;
	while (p1 != NULL)
	{
		p1->rank = 0;
		p1 = p1->next;
	}
	p1 = envp;
	while (p1 != NULL)
	{
		p2 = envp;
		while (p2 != NULL)
		{
			if (ft_strcmp(p1->content, p2->content) < 0)
				p2->rank += 1;
			p2 = p2->next;
		}
		p1 = p1->next;
	}
}

static void	print_envp(t_envp *envp)
{
	t_envp		*p;
	int			i;
	int			max_rank;
	static int	is_not_first_export;

	sort_envp(envp);
	max_rank = get_max_rank(envp);
	i = 0;
	while (i++ <= max_rank)
	{
		p = envp;
		while (p != NULL)
		{
			if (p->rank == i)
			{
				if ((p->content)[0] == '_' && (p->content)[1] == '='
					&& is_not_first_export)
					break ;
				if ((p->content)[0] == '_' && (p->content)[1] == '=')
					is_not_first_export++;
				print_envp_content(p->content);
			}
			p = p->next;
		}
	}
}

static void	print_envp_content(char *content)
{
	int		is_first_equal;
	size_t	i;

	printf("declare -x ");
	is_first_equal = 1;
	i = 0;
	while (content[i] != '\0')
	{
		printf("%c", content[i]);
		if (content[i] == '=' && is_first_equal)
		{
			printf("%c", '\"');
			is_first_equal = 0;
		}
		++i;
	}
	if (content[i] == '\0' && !is_first_equal)
		printf("%c", '\"');
	printf("\n");
}
/* 
//debug
int	main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	t_envp	*envp_list;
	char	now_path[512];

	res = parser(av[1]);
	envp_list = get_envp_list(envp);
	exec(res, &envp_list);
	//system("export");
	print_envp(envp_list);
	//system("leaks -q a.out");
	return (0);
}
 */