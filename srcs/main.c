/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko </var/mail/kkaneko>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/20 14:52:35 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_arg_err(int ac, char **av, char **envp);
static int	prompt(void);

int	main(int ac, char **av, char **envp)
{
	char	*input;

	if (get_arg_err(ac, av, envp))
		return (1);
	prompt();
	return (0);
}

static int	get_arg_err(int ac, char **av, char **envp)
{
	if (envp == NULL)
		return (1);
	return (0);
}

static int	prompt(void)
{
	char	*input;

	while (1)
	{
		input = readline(SHELL_NAME);
		parse(input);
		expand_var(input);
		exec_cmd();
	}
	return (0);
}
