/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:39:05 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/18 19:15:10 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*make_new_path_argc_0_or_1(t_cmd *input, t_envp *envp);
static char	*make_new_path_argc_2(t_cmd *input);
static char	*get_new_path_argc_2(
				char *now_path, char *old, char *new, char *old_found_p);
static int	is_empty_str(char *s);

void	cd(t_cmd *input, t_envp *envp)
{
	int		argc;
	char	*new_path;

	argc = ft_lstsize(input->args);
	new_path = NULL;
	if (argc == 0 || argc == 1)
		new_path = make_new_path_argc_0_or_1(input, envp);
	else if (argc == 2)
		new_path = make_new_path_argc_2(input);
	else
		printf("cd: too many arguments\n");
	if (new_path == NULL)
		return ;
	if (chdir(new_path))
		printf("cd: no such file or directory: %s\n", new_path);
	free(new_path);
}

static char	*make_new_path_argc_0_or_1(t_cmd *input, t_envp *envp)
{
	if (input->args == NULL || is_empty_str(input->args->content)
		|| ft_strncmp(input->args->content, "~", 2) == 0)
	{
		if (ft_getenv("HOME", envp) == NULL)
			return (ft_strdup(getenv("HOME")));
		return (ft_strdup(ft_getenv("HOME", envp)));
	}
	else if (ft_strncmp(input->args->content, "~/", 2) == 0)
	{
		if (ft_getenv("HOME", envp) == NULL)
			return (three_strjoin(getenv("HOME"), "/", &(input->args->content)[2]));
		return (three_strjoin(ft_getenv("HOME", envp), "/", &(input->args->content)[2]));
	}
	return (ft_strdup(input->args->content));
}

static char	*make_new_path_argc_2(t_cmd *input)
{
	char	now_path[512];
	char	*old;
	char	*new;
	char	*new_path;
	char	*old_found_p;

	getcwd(now_path, 512);
	old = input->args->content;
	new = input->args->next->content;
	old_found_p = ft_strnstr(now_path, old, ft_strlen(now_path));
	if (old_found_p == NULL)
	{
		printf("cd: string not in pwd: %s\n", old);
		return (NULL);
	}
	new_path = get_new_path_argc_2(now_path, old, new, old_found_p);
	return (new_path);
}

static char	*get_new_path_argc_2(
	char *now_path, char *old, char *new, char *old_found_p)
{
	char	*new_path;
	size_t	i;

	new_path = (char *)malloc(sizeof(char)
			* (ft_strlen(now_path) - ft_strlen(old) + ft_strlen(new) + 1));
	if (new_path == NULL)
		return (NULL);
	i = 0;
	while (&now_path[i] != old_found_p)
	{
		new_path[i] = now_path[i];
		++i;
	}
	ft_memmove(&new_path[i], new, ft_strlen(new));
	i += ft_strlen(new);
	old_found_p += ft_strlen(old);
	while (*old_found_p != 0x00)
	{
		new_path[i] = *old_found_p;
		++i;
		++old_found_p;
	}
	new_path[i] = 0x00;
	return (new_path);
}

static int	is_empty_str(char *s)
{
	if (s[0] == 0x00)
		return (1);
	return (0);
}
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
	getcwd(now_path, 512);
	printf("before_path = %s\n\n", now_path);
	exec(res);
	//chdir("..");
	//chdir("abcdabc");
	getcwd(now_path, 512);
	printf("\nafter_path = %s\n", now_path);
	return (0);
} */