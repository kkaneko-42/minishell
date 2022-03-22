/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:28:22 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/23 01:03:58 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <limits.h>

static char	*get_exit_num(char *content);
static int	is_number(const char *exit_num);
static int	is_valid_size(const char *exit_num);

void	exit_builtin(t_cmd *input)
{
	int				argc;
	char			*exit_num;

	ft_putstr_fd(EXIT_MSG, STDERR_FILENO);
	argc = ft_lstsize(input->args);
	if (argc == 0)
		exit(0);
	exit_num = get_exit_num(input->args->content);
	if (!is_number(exit_num) || !is_valid_size(exit_num))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(exit_num, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(UCHAR_MAX);
	}
	else if (argc >= 2)
		ft_putendl_fd("minishell: exit:  too many arguments", STDERR_FILENO);
	else
		exit((unsigned char)ft_atoi(exit_num));
}

static char	*get_exit_num(char *content)
{
	size_t	i;

	i = 0;
	while (content[i] == ' ')
		++i;
	if (content[i] == '+')
		++i;
	return (&content[i]);
}

static int	is_number(const char *exit_num)
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

static int	is_valid_size(const char *exit_num)
{
	if (exit_num[0] == '-')
	{
		if (ft_strlen(exit_num) > ft_strlen(LLONG_MIN_STR)
			|| ft_atoi(exit_num) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(exit_num) > ft_strlen(LLONG_MAX_STR)
			|| ft_atoi(exit_num) < 0)
			return (0);
	}
	return (1);
}

//+42みたいなとき
