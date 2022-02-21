/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/21 21:43:48 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_token(const t_list *token);
static int	metachar_isin_token(const t_list *token);
static t_cmd	*cmd_new(char *name);
static void	cmdadd_back(t_cmd **lst, t_cmd *new);
static void	get_cmd_args(t_cmd *cmd, t_list **token);

t_cmd	*parser(const char *input)
{
	t_list	*token;
	t_cmd	*res;
	t_cmd	*now_cmd;

	token = lexer(input);
	validate_token(token);
	res = INIT;
	now_cmd = NULL;
	while (token != NULL)
	{
		cmdadd_back(&now_cmd, cmd_new(token->content));
		if (res == INIT)
			res = now_cmd;
		token = token->next;
		get_cmd_args(now_cmd, &token);
	}
	return (res);
}

static void	validate_token(const t_list *token)
{
	//if tokens have an error, exit
	if (token == NULL)
		exit(1);
}

static t_cmd	*cmd_new(char *name)
{
	t_cmd	*res;

	res = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->name = name;
	return (res);
}

static void	cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*now;

	if (*lst == NULL)
		*lst = new;
	else
	{
		now = *lst;
		while (now->next != NULL)
			now = now->next;
		now->next = new;
		new->prev = now;
	}
}

static int	metachar_isin_token(const t_list *token)
{
	const size_t	search_len = ft_strlen(token->content);

	if (ft_strnstr(token->content, "><|", search_len) != NOT_FOUND)
		return (1);
	else
		return (0);
}

static void	get_cmd_args(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL && !metachar_isin_token(*token))
	{
		ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup((*token)->content)));
		*token = (*token)->next;
	}
	//metachar process func
}
/*
//debug
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;

	res = parser(av[1]);
	for (t_cmd *now = res; now != NULL; now = now->next)
	{
		printf("cmd name:@%s@\n", now->name);
		printf("args:\n");
		for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
			printf("@%s@\n", arg_now->content);
	}
	return (0);
}
*/