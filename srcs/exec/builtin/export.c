/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:38:14 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/06/04 12:23:45 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_envp(t_envp *envp);
static void	print_envp(t_cmd *input, t_envp *envp);
static void	print_envp_content(t_cmd *input, const char *content);
static int	add_env(t_envp **env_list, char *content);

int	export(t_cmd *input, t_envp *envp)
{
	const int	argc = ft_lstsize(input->args);
	t_list		*p_args;
	int			fg_err;

	fg_err = 0;
	if (argc == 0)
		print_envp(input, envp);
	else
	{
		p_args = input->args;
		while (p_args != NULL)
		{
			fg_err += add_env(&envp, p_args->content);
			p_args = p_args->next;
		}
	}
	if (fg_err)
		return (CMD_ERR);
	return (CMD_SUCCESS);
}

static int	add_env(t_envp **env_list, char *content)
{
	if (forbidden_char_is_exist_in_envp(content))
		return (identifier_err("export", content));
	else if (is_exist_env(*env_list, content) == 1)
	{
		delete_env(env_list, content);
		addback_envp_list(env_list, content);
	}
	else if (is_exist_env(*env_list, content) != 2)
		addback_envp_list(env_list, content);
	return (CMD_SUCCESS);
}

static void	sort_envp(t_envp *envp)
{
	t_envp	*cmp_standard;
	t_envp	*p_envp;

	p_envp = envp;
	while (p_envp != NULL)
	{
		p_envp->rank = 0;
		p_envp = p_envp->next;
	}
	cmp_standard = envp;
	while (cmp_standard != NULL)
	{
		p_envp = envp;
		while (p_envp != NULL)
		{
			if (ft_envcmp(cmp_standard->content, p_envp->content) < 0)
				p_envp->rank += 1;
			p_envp = p_envp->next;
		}
		cmp_standard = cmp_standard->next;
	}
}

static void	print_envp(t_cmd *input, t_envp *envp)
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
				print_envp_content(input, p->content);
			}
			p = p->next;
		}
	}
}

static void	print_envp_content(t_cmd *input, const char *content)
{
	int		fg_first_equal;
	size_t	i;

	ft_putstr_fd("declare -x ", input->fd_out);
	fg_first_equal = 1;
	i = 0;
	while (content[i] != '\0')
	{
		ft_putchar_fd(content[i], input->fd_out);
		if (content[i] == '=' && fg_first_equal)
		{
			ft_putstr_fd("\"", input->fd_out);
			fg_first_equal = 0;
		}
		++i;
	}
	if (content[i] == '\0' && !fg_first_equal)
		ft_putstr_fd("\"", input->fd_out);
	ft_putstr_fd("\n", input->fd_out);
}
