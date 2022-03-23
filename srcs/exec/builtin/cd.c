/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 08:39:05 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 22:13:02 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_new_path(t_cmd *input, t_envp *envp);

int	cd(t_cmd *input, t_envp *envp)
{
	char	*old_path;
	char	*new_path;
	int		ret;

	old_path = get_now_path();
	new_path = get_new_path(input, envp);
	errno = 0;
	if (chdir(new_path))
	{
		cd_err(input);
		ret = 1;
	}
	else
	{
		cd_set_env(envp, old_path);
		ret = 0;
	}
	free(old_path);
	free(new_path);
	return (ret);
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
