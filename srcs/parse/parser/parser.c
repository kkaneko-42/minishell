/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/17 18:52:11 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*tokenize(const char *input, t_envp *env_list);
static t_cmd	*set_cmd_info(t_list *token);
void			parse_metachar(t_cmd *cmd, t_list **token);
static t_list	*get_metachar_list(void);

t_cmd	*parser(const char *input, t_envp *env_list)
{
	t_list	*token;
	t_list	*now_token;
	t_cmd	*res;
	t_cmd	*now_cmd;

	token = tokenize(input, env_list);
	if (validate_token(token))
	{
		ft_lstclear(&token, free_content);
		return (NULL);
	}
	res = set_cmd_info(token);
	ft_lstclear(&token, free_content);
	return (res);
}

static t_cmd	*set_cmd_info(t_list *token)
{
	t_cmd	*cmd_lst;
	t_cmd	*now_cmd;
	t_list	*now_token;

	cmd_lst = NULL;
	now_token = token;
	now_cmd = INIT;
	while (now_token != NULL)
	{
		cmdadd_back(&cmd_lst, cmd_new(ft_strdup(now_token->content)));
		if (now_cmd == INIT)
			now_cmd = cmd_lst;
		else
			now_cmd = now_cmd->next;
		now_token = now_token->next;
		get_cmd_info(now_cmd, &now_token);
	}
	remove_quotes_from_cmds(cmd_lst);
	return (cmd_lst);
}

static t_list	*tokenize(const char *input, t_envp *env_list)
{
	t_list	*token;

	token = lexer(input);
	expand_env(token, env_list);
	re_lexer(&token);
	refact_token(&token);
	return (token);
}

void	parse_metachar(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL && is_metachar((*token)->content))
	{
		if (ft_strncmp((*token)->content, "|", 2) == 0)
			break ;
		else if (ft_strncmp((*token)->content, "<", 2) == 0)
			input_file_specify(cmd, token);
		else if (ft_strncmp((*token)->content, "<<", 3) == 0)
			heredoc(cmd, token);
		else if (ft_strncmp((*token)->content, ">>", 3) == 0)
			output_file_specify(cmd, token, O_APPEND);
		else if (ft_strncmp((*token)->content, ">", 2) == 0)
			output_file_specify(cmd, token, !O_APPEND);
		*token = (*token)->next;
	}
}

/*
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	char	*input = "echo hello > ";
	t_envp	*env_list = get_envp_list(envp);

	res = parser(input, env_list);
	for (t_cmd *now = res; now != NULL; now = now->next)
	{
		printf("cmd name:@%s@\n", now->name);
		printf("output fd:%d\n", now->fd_out);
		printf("args:\n");
		for (t_list *arg_now = now->args; arg_now != NULL; arg_now = arg_now->next)
		{
			printf("@%s@\n", arg_now->content);
		}
	}
	return (0);
}
*/
