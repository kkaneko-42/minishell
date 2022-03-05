/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:17:06 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/04 16:12:11 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		validate_args(int ac, char **av, char **envp);
static t_list 	*envp_to_list(char **envp);
static void		prompt(t_envp *env_list);

int	main(int ac, char **av, char **envp)
{
	//t_list	*env_list;
	t_envp	*env_list;

	validate_args(ac, av, envp);
	env_list = get_envp_list(envp);
	prompt(env_list);
	return (0);
}

static void	validate_args(int ac, char **av, char **envp)
{
	if (envp == NULL)
		exit(1);
}

t_envp	*get_envp_list(char **envp)
{
	t_envp	*envp_list;
	size_t	i;

	envp_list = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (!addback_envp_list(&envp_list, envp[i])) //malloc err
		{
			//free
			//exit
			//return (NULL);
		}
		++i;
	}
	return (envp_list);
}

int	addback_envp_list(t_envp **envp_list, char *s)
{
	t_envp	*new_envp;
	t_envp	*p;

	new_envp = (t_envp *)malloc(sizeof(t_envp) * 1);
	if (new_envp == NULL)
		return (0);
	new_envp->content = ft_strdup(s);
	new_envp->rank = 0;
	if (new_envp->content == NULL)
		return (0);
	if (*envp_list == NULL)
	{
		new_envp->next = NULL;
		new_envp->prev = NULL;
		*envp_list = new_envp;
		return (1);
	}
	p = *envp_list;
	while (p->next != NULL)
		p = p->next;
	p->next = new_envp;
	new_envp->next = NULL;
	new_envp->prev = p;
	return (1);
}

static void	prompt(t_envp *env_list)
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
		exec(cmd, &env_list);
		free(input);
	}
}
