/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:28:22 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/03/27 11:29:24 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include <limits.h>

static char	*get_exit_status(char *content);
static int	is_number(const char *exit_status);
static int	is_valid_size(const char *exit_status);

int	exit_builtin(t_cmd *input)
{
	const int	argc = ft_lstsize(input->args);
	char		*exit_status;

	ft_putstr_fd(EXIT_MSG, STDERR_FILENO);
	if (argc == 0)
		exit(CMD_SUCCESS);
	exit_status = get_exit_status(input->args->content);
	if (!is_number(exit_status) || !is_valid_size(exit_status))
	{
		num_arg_required_err(exit_status);
		exit(UCHAR_MAX);
	}
	else if (argc >= 2)
		return (too_many_args_err("exit"));
	else
		exit((unsigned char)ft_atoi(exit_status));
}

static char	*get_exit_status(char *content)
{
	size_t	i;

	i = 0;
	while (content[i] == ' ')
		++i;
	if (content[i] == '+')
		++i;
	return (&content[i]);
}

static int	is_number(const char *exit_status)
{
	size_t	i;

	i = 0;
	if (exit_status[0] == '-')
		++i;
	while (exit_status[i] != '\0')
	{
		if (!ft_isdigit(exit_status[i]))
			return (0);
		++i;
	}
	return (1);
}

static int	is_valid_size(const char *exit_status)
{
	if (exit_status[0] == '-')
	{
		if (ft_strlen(exit_status) > ft_strlen(LLONG_MIN_STR)
			|| ft_atoi(exit_status) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(exit_status) > ft_strlen(LLONG_MAX_STR)
			|| ft_atoi(exit_status) < 0)
			return (0);
	}
	return (1);
}
