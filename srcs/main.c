/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/19 19:03:49 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void		validate_args(int ac, char **av, char **envp);
static void		sig_handler(sig_atomic_t sig);
static void		prompt(t_envp *env_list);

int	main(int ac, char **av, char **envp)
{
	t_envp	*env_list;

	validate_args(ac, av, envp);
	receiver(sig_handler);
	env_list = get_envp_list(envp);
	prompt(env_list);
	free_envp_list(&env_list, free_content);
	return (0);
}

static void	prompt(t_envp *env_list)
{
	char	*input;
	t_cmd	*cmd;

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
		{
			add_history(input);
			cmd = parser(input, env_list);
			if (cmd != NULL)
			{
				/*
				for (t_cmd *now = cmd; now != NULL; now = now->next)
				{
					printf("cmd name:@%s@\n", now->name);
					printf("fd_out: %d\n", now->fd_out);
					printf("args:\n");
					for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
						printf("@%s@\n", arg_now->content);
					printf("stdin_str:\n%s\n", now->stdin_str);
					printf("-------------\n");
				}
				*/
				exec(cmd, &env_list);
				free_cmds(cmd);
			}
		}
		free(input);
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
	return ;
}
