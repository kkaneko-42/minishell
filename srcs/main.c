/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/02 22:43:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		validate_args(int ac, char **av, char **envp);
static t_list 	*envp_to_list(char **envp);
static void		prompt(t_list *env_list);

int	main(int ac, char **av, char **envp)
{
	t_list	*env_list;

	validate_args(ac, av, envp);
	env_list = envp_to_list(envp);
	prompt(env_list);
	return (0);
}

static void	validate_args(int ac, char **av, char **envp)
{
	if (envp == NULL)
		exit(1);
}

static t_list	*envp_to_list(char **envp)
{
	size_t	i;
	t_list	*res;

	i = 0;
	res = NULL;
	while (envp[i] != NULL)
	{
		ft_lstadd_back(&res, ft_strdup(envp[i]));
		++i;
	}
	return (res);
}

static void	prompt(t_list *env_list)
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
