/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:39:05 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/21 00:16:37 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_new_path(t_cmd *input, t_envp *envp);
static int	is_empty_str(const char *s);

void	cd(t_cmd *input, t_envp *envp)
{
	int		argc;
	char	*new_path;
	char	*old_pwd;
	char	*old_pwd_env;
	char	*pwd_env;

	new_path = get_new_path(input, envp);
	errno = 0;
	if (chdir(new_path))
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		if (input->args != NULL)
			ft_putstr_fd(input->args->content, STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
	{
		if (ft_getenv("PWD", envp) == NULL)
			old_pwd = ft_strdup("\0");
		else
			old_pwd = ft_strdup(ft_getenv("PWD", envp));
		delete_env(&envp, "PWD");
		delete_env(&envp, "OLDPWD");
		old_pwd_env = ft_strjoin("OLDPWD=", old_pwd);
		addback_envp_list(&envp, old_pwd_env);
		free(old_pwd);
		free(old_pwd_env);
		pwd_env = ft_strjoin("PWD=", get_now_path());
		addback_envp_list(&envp, pwd_env);
		free(pwd_env);
	}
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
			return (three_strjoin(getenv("HOME"), "/", &(input->args->content)[2]));
		return (three_strjoin(ft_getenv("HOME", envp), "/", &(input->args->content)[2]));
	}
	return (ft_strdup(input->args->content));
}

static int	is_empty_str(const char *s)
{
	if (s[0] == '\0')
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