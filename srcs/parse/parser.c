/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/16 01:32:10 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		validate_token(const t_list *token);
static t_cmd	*cmd_new(char *name);
static void	cmdadd_back(t_cmd **lst, t_cmd *new);
static void	get_cmd_info(t_cmd *cmd, t_list **token);
static void	get_cmd_args(t_cmd *cmd, t_list **token);
static void	parse_metachar(t_cmd *cmd, t_list **token);
static char	*get_file_content_all(int fd);
static void	input_file_specify(t_cmd *cmd, t_list **token);
static void	heredoc(t_cmd *cmd, t_list **token);
static void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append);
static t_list	*get_metachar_list(void);
static char	*get_heredoc_input(const char *end_text);

t_cmd	*parser(const char *input, t_envp *env_list)
{
	t_list	*token;
	t_cmd	*res;
	t_cmd	*now_cmd;
	
	token = lexer(input);
	expand_env(token, env_list);
	re_lexer(&token);
	refact_token(&token);
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

static void	get_cmd_info(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL)
	{
		if (ft_strncmp((*token)->content, "|", 2) == 0)
		{
			(*token) = (*token)->next;
			break ;
		}
		get_cmd_args(cmd, token);
		parse_metachar(cmd, token);
	}
}

static void	get_cmd_args(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL && !is_metachar((*token)->content))
	{
		ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup((*token)->content)));
		*token = (*token)->next;
	}
}

static void	parse_metachar(t_cmd *cmd, t_list **token)
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

static void	input_file_specify(t_cmd *cmd, t_list **token)
{
	int		input_fd;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	input_fd = open((*token)->content, O_RDONLY);
	if (input_fd == -1)
		; //open err
	cmd->stdin_str = get_file_content_all(input_fd);
}

static void	heredoc(t_cmd *cmd, t_list **token)
{
	char	*end_text;
	char	*line;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	end_text = (*token)->content;
	cmd->stdin_str = get_heredoc_input(end_text);
}

static char	*get_heredoc_input(const char *end_text)
{
	char	*line;
	char	*res;

	res = NULL;
	line = readline(HEREDOC_PROMPT);
	while (line != NULL && ft_strncmp(line, end_text, ft_strlen(end_text) + 1) != 0)
	{
		res = ft_stradd(&res, line);
		res = ft_stradd(&res, "\n");
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	//eof validation
	free(line);
	return (res);
}

static void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append)
{
	const mode_t	out_file_rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int		open_flags = O_RDWR | O_CREAT | fg_append;
	int				fd_out;

	*token = (*token)->next;
	remove_quotes(&((*token)->content));
	if (fg_append != O_APPEND)
	{
		if (unlink((*token)->content))
			; //unlink err
	}
	//other flags(eg:O_CLOEXEC) may be needed
	fd_out = open((*token)->content, open_flags, out_file_rights);
	//open err
	cmd->fd_out = fd_out;
}

static char	*get_file_content_all(int fd)
{
	char	*res;
	char	*tmp;

	res = NULL;
	tmp = get_next_line(fd);
	while (tmp != NULL) //EOF?error?
	{
		res = ft_stradd(&res, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	return (res);
}

static t_cmd	*cmd_new(char *name)
{
	t_cmd	*res;

	res = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (res == NULL)
		return (NULL);
	res->name = name;
	res->fd_out = 1;
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

static int	validate_token(const t_list *token)
{
	//if tokens have an error, exit
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
