/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/05 23:00:42 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

static void		validate_args(int ac, char **av, char **envp);
static void		prompt(t_envp **env_list);
static void		parse_and_execute(const char *input, t_envp **env_list);

int	main(int ac, char **av, char **envp)
{
	t_envp	*env_list;

	validate_args(ac, av, envp);
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
		receiver_for_readline();
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
		receiver_for_exec();
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
