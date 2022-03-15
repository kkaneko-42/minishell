/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 16:34:17 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static sig_atomic_t	g_sig;

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

			for (t_cmd *now = cmd; now != NULL; now = now->next)
			{
				printf("cmd name:@%s@\n", now->name);
				printf("fd_out: %d\n", now->fd_out);
				printf("args:\n");
				for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
					printf("@%s@\n", arg_now->content);
			}
			printf("-------------\n");
      
			exec(cmd, &env_list);
			//free cmd;
		}
		free(input);
	}
}

static void	validate_args(int ac, char **av, char **envp)
{
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
}
