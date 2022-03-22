/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:39:05 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 00:59:21 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_new_path(t_cmd *input, t_envp *envp);

void	cd(t_cmd *input, t_envp *envp)
{
	char	*old_path;
	char	*new_path;

	old_path = get_now_path();
	new_path = get_new_path(input, envp);
	errno = 0;
	if (chdir(new_path))
		cd_err(input);
	else
		set_pwd_and_old_pwd(envp, old_path);
	free(old_path);
	free(new_path);
}

static char	*get_new_path(t_cmd *input, t_envp *envp)
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
			return (three_strjoin(
					getenv("HOME"), "/", &(input->args->content)[2]));
		return (three_strjoin(
				ft_getenv("HOME", envp), "/", &(input->args->content)[2]));
	}
	return (ft_strdup(input->args->content));
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