/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:07:40 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 01:39:35 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	delete_first_node(t_envp **envp, t_envp **p_envp);
static void	delete_last_node(t_envp **p_envp);
static void	delete_between_node(t_envp **p_envp);
static void	delete_env_unset(t_envp **envp, t_list *p_args);

void	unset(t_cmd *input, t_envp **envp)
{
	int		argc;
	t_list	*p_args;

	argc = ft_lstsize(input->args);
	if (argc == 0)
		return ;
	p_args = input->args;
	while (p_args != NULL)
	{
		if (forbidden_char_is_exist_in_envp(p_args->content))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(p_args->content, STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		}
		else
			delete_env_unset(envp, p_args);
		p_args = p_args->next;
	}
}

static void	delete_env_unset(t_envp **envp, t_list *p_args)
{
	t_envp	*p_envp;
	size_t	args_len;

	p_envp = *envp;
	while (p_envp != NULL)
	{
		args_len = ft_strlen(p_args->content);
		if (ft_strncmp(p_args->content, p_envp->content, args_len) == 0
			&& ((p_envp->content)[args_len] == '='
			|| (p_envp->content)[args_len] == '\0'))
		{
			if (p_envp->prev == NULL)
				delete_first_node(envp, &p_envp);
			else if (p_envp->next == NULL)
				delete_last_node(&p_envp);
			else
				delete_between_node(&p_envp);
			break ;
		}
		else
			p_envp = p_envp->next;
	}
}

static void	delete_first_node(t_envp **envp, t_envp **p_envp)
{
	t_envp	*tmp;

	if ((*p_envp)->next == NULL)
	{
		free((*p_envp)->content);
		(*p_envp)->content = NULL;
		free(*p_envp);
		*p_envp = NULL;
	}
	else
	{
		tmp = *p_envp;
		(*p_envp)->next->prev = NULL;
		*envp = (*p_envp)->next;
		*p_envp = (*p_envp)->next;
		free(tmp->content);
		tmp->content = NULL;
		free(tmp);
		tmp = NULL;
	}
}

static void	delete_last_node(t_envp **p_envp)
{
	(*p_envp)->prev->next = NULL;
	free((*p_envp)->content);
	(*p_envp)->content = NULL;
	free(*p_envp);
	*p_envp = NULL;
}

static void	delete_between_node(t_envp **p_envp)
{
	t_envp	*tmp;
	t_envp	*next;

	tmp = *p_envp;
	(*p_envp)->prev->next = (*p_envp)->next;
	(*p_envp)->next->prev = (*p_envp)->prev;
	(*p_envp) = (*p_envp)->next;
	free(tmp->content);
	tmp->content = NULL;
	free(tmp);
	tmp = NULL;
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
	exec(res, envp_list);
	//system("export");
	//print_envp(envp_list);
	//system("leaks -q a.out");
	return (0);
} */
