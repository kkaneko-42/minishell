/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:28:22 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/19 00:58:39 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_number(char *exit_num);
static int	is_valid_size(char *exit_num);

void	exit_builtin(t_cmd *input)
{
	int				argc;
	unsigned char	res;
	char			*exit_num;

	ft_putendl_fd("exit", 1);
	argc = ft_lstsize(input->args);
	if (argc == 0)
		exit(0);
	exit_num = input->args->content;
	if (!is_number(exit_num) || !is_valid_size(exit_num))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(exit_num, 1);
		ft_putendl_fd(": numeric argument required", 1);
		exit(255);
	}
	else if (argc >= 2)
	{
		ft_putendl_fd("minishell: exit:  too many arguments", 1);
	}
	else
	{
		exit((unsigned char)ft_atoi(exit_num));
	}	
	//$?の設定いらない?
}

static int	is_number(char *exit_num)
{
	size_t	i;

	i = 0;
	if (exit_num[0] == '-')
		++i;
	while (exit_num[i] != '\0')
	{
		if (!ft_isdigit(exit_num[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	is_valid_size(char *exit_num)
{
	if (exit_num[0] == '-')
	{
		if (ft_strlen(exit_num) > ft_strlen("-9223372036854775808")
			|| ft_atoi(exit_num) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(exit_num) > ft_strlen("9223372036854775807")
			|| ft_atoi(exit_num) < 0)
			return (0);
	}
	return (1);
}

//+42みたいなとき
