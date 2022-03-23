/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/24 00:44:07 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void		validate_args(int ac, char **av, char **envp);
static void		sig_handler(sig_atomic_t sig);
static void		prompt(t_envp **env_list);
static void		parse_and_execute(const char *input, t_envp **env_list);

int	main(int ac, char **av, char **envp)
{
	t_envp	*env_list;

	validate_args(ac, av, envp);
	receiver(sig_handler);
	env_list = get_envp_list(envp);
	put_title();
	prompt(&env_list);
	free_envp_list(&env_list, free_content);
	return (0);
}

static void	prompt(t_envp **env_list)
{
	char	*input;

	input = NULL;
	while (1)
	{
		input = readline(SHELL_NAME);
		if (input == NULL)
		{
			printf(EXIT_MSG);
			break ;
		}
		if (ft_strlen(input) > 0)
			parse_and_execute(input, env_list);
		free(input);
	}
}

static void	parse_and_execute(const char *input, t_envp **env_list)
{
	t_cmd	*cmd;

	add_history(input);
	cmd = parser(input, *env_list);
	if (cmd != NULL)
	{
		exec(cmd, env_list);
		free_cmds(cmd);
	}
}

static void	validate_args(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	if (envp == NULL)
		exit(1);
}

static void	sig_handler(sig_atomic_t sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}
