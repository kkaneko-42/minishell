/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:07:40 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/27 11:34:44 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	unset(t_cmd *input, t_envp **envp)
{
	const int	argc = ft_lstsize(input->args);
	t_list		*p_args;

	if (argc == 0)
		return (CMD_SUCCESS);
	p_args = input->args;
	while (p_args != NULL)
	{
		if (forbidden_char_is_exist_in_envp(p_args->content))
			return (identifier_err("unset", p_args->content));
		else
			delete_env(envp, p_args->content);
		p_args = p_args->next;
	}
	return (CMD_SUCCESS);
}
