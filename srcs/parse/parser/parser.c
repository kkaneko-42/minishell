/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/16 17:19:46 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_list	*tokenize(const char *input, t_envp *env_list);
static int		validate_token(const t_list *token);
void			parse_metachar(t_cmd *cmd, t_list **token);
static t_list	*get_metachar_list(void);

t_cmd	*parser(const char *input, t_envp *env_list)
{
	t_list	*token;
	t_cmd	*res;
	t_cmd	*now_cmd;

	token = tokenize(input, env_list);
	if (validate_token(token))
		return (NULL); //Todo: free tokens
	res = NULL;
	now_cmd = INIT;
	while (token != NULL)
	{
		cmdadd_back(&res, cmd_new(token->content));
		if (now_cmd == INIT)
			now_cmd = res;
		else
			now_cmd = now_cmd->next;
		token = token->next;
		get_cmd_info(now_cmd, &token);
	}
	remove_quotes_from_cmds(res);
	return (res);
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

static int	validate_token(const t_list *token)
{
	if (check_metachar_target(token)
		|| check_nb_quotes(token))
	{
		ft_putstr_fd(PARSE_ERR, STDERR_FILENO);
		return (1);
	}
	return (0);
}

//debug
void	put_all_tokens(t_list *tokens)
{
	for (t_list *now = tokens; now != NULL; now = now->next)
	{
		printf("===============================\n");
		printf("content:%s\n", now->content);
		printf("prev:%p\n", now->prev);
		printf("now:%p\n", now);
		printf("next:%p\n", now->next);
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
