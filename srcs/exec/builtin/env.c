/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 11:30:28 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/06 16:20:05 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_env(t_envp *envp);
static int	have_equal(char *s);

void	env(t_cmd *input, t_envp *envp)
{
	int	argc;

	argc = ft_lstsize(input->args);
	if (argc == 0)
		print_env(envp);
	else
		printf("env: too many arguments\n");
}

static void	print_env(t_envp *envp)
{
	t_envp	*p;

	p = envp;
	while (p != NULL)
	{
		if (have_equal(p->content)
			&& !forbidden_char_is_exist_in_envp(p->content))
			printf("%s\n", p->content);
		p = p->next;
	}
}

static int	have_equal(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		++i;
	}
	return (0);
}
/* 
int	is_builtin(t_cmd *input)
{
	char	*new_input;
	t_cmd	*new_cmd_list;
	
	if (!ft_strncmp(input->args->content, "echo", 5)
	|| !ft_strncmp(input->args->content, "cd", 3)
	|| !ft_strncmp(input->args->content, "pwd", 4)
	|| !ft_strncmp(input->args->content, "export", 7)
	|| !ft_strncmp(input->args->content, "unset", 6)
	|| !ft_strncmp(input->args->content, "env", 4)
	|| !ft_strncmp(input->args->content, "exit", 5))
	{
		
		new_cmd_list = ;
	}
} */

/* 
//debug
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	char	now_path[512];

	res = parser(av[1]);
	for (t_cmd *now = res; now != NULL; now = now->next)
	{
		printf("cmd name:@%s@\n", now->name);
		printf("args:\n");
		for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
			printf("@%s@\n", arg_now->content);
	}
	exec(res, envp);
	return (0);
}
*/