/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/02 22:18:12 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


static void	validate_args(int ac, char **av, char **envp);
static void	prompt(char **envp);

int	main(int ac, char **av, char **envp)
{
	validate_args(ac, av, envp);
	prompt(envp);
	return (0);
}

static void	prompt(char **envp)
{
	char	*input;
	t_cmd	*cmd;

	while (1)
	{
		input = readline(SHELL_NAME);
		if (input == NULL)
		{
			printf(EXIT_MSG);
			break ;
		}
		add_history(input);
		cmd = parser(input);
		//expand_var(cmd, envp);
		exec(cmd); //exec(cmd, envp);
		free(input);
	}
}

static void	validate_args(int ac, char **av, char **envp)
{
	if (envp == NULL)
		exit(1);
}