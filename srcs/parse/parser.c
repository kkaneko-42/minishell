/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/03 17:54:06 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_token(const t_list *token);
static int	metachar_isin_token(const t_list *token);
static t_cmd	*cmd_new(char *name);
static void	cmdadd_back(t_cmd **lst, t_cmd *new);
static void	get_cmd_args(t_cmd *cmd, t_list **token);
static void	parse_metachar(t_cmd *cmd, t_list **token);
static char	*get_file_content_all(int fd);
static void	input_file_specify(t_cmd *cmd, t_list **token);
static void	heredoc(t_cmd *cmd, t_list **token);
static void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append);

t_cmd	*parser(const char *input)
{
	t_list	*token;
	t_cmd	*res;
	t_cmd	*now_cmd;

	token = lexer(input);
	validate_token(token);
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
		get_cmd_args(now_cmd, &token);
		parse_metachar(now_cmd, &token);
	}
	return (res);
}

static void	get_cmd_args(t_cmd *cmd, t_list **token)
{
	int	input_fd;

	while ((*token) != NULL && !metachar_isin_token(*token))
	{
		ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup((*token)->content)));
		*token = (*token)->next;
	}
}

static void	parse_metachar(t_cmd *cmd, t_list **token)
{
	while ((*token) != NULL && metachar_isin_token(*token))
	{
		if (ft_strncmp((*token)->content, "<", 2) == 0)
			input_file_specify(cmd, token);
		else if (ft_strncmp((*token)->content, "<<", 3) == 0)
			heredoc(cmd, token);
		else if (ft_strncmp((*token)->content, ">>", 3) == 0)
			output_file_specify(cmd, token, O_APPEND);
		else if (ft_strncmp((*token)->content, ">", 2) == 0)
			output_file_specify(cmd, token, !O_APPEND);
		else if (ft_strncmp((*token)->content, "|", 2) == 0)
		{
			*token = (*token)->next;
			break ;
		}
		*token = (*token)->next;
	}
}

static void	input_file_specify(t_cmd *cmd, t_list **token)
{
	int		input_fd;
	char	*file_content;

	*token = (*token)->next;
	input_fd = open((*token)->content, O_RDONLY);
	if (input_fd == -1)
		; //open err
	file_content = get_file_content_all(input_fd);
	ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup(file_content)));
	free(file_content);
}

static void	heredoc(t_cmd *cmd, t_list **token)
{
	char	*end_text;
	char	*cmd_arg;
	char	*line;

	*token = (*token)->next;
	end_text = (*token)->content;
	cmd_arg = NULL;
	line = readline(HEREDOC_PROMPT);
	while (line != NULL && ft_strncmp(line, end_text, ft_strlen(end_text) + 1) != 0)
	{
		cmd_arg = ft_stradd(&cmd_arg, line);
		cmd_arg = ft_stradd(&cmd_arg, ft_strdup("\n"));
		free(line);
		line = readline(HEREDOC_PROMPT);
	}
	free(line);
	ft_lstadd_back(&(cmd->args), ft_lstnew(ft_strdup(cmd_arg)));
	free(cmd_arg);
}

static void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append)
{
	const mode_t	out_file_rights = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	const int		open_flags = O_RDWR | O_CREAT | fg_append;
	int				fd_out;

	*token = (*token)->next;
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
	const char	metachar[4] = "><|";
	size_t		i;

	i = 0;
	while (i < ft_strlen(metachar))
	{
		if (ft_strchr(token->content, metachar[i]) != NOT_FOUND)
			return (1);
		++i;
	}
	return (0);
}

static void	validate_token(const t_list *token)
{
	//if tokens have an error, exit
	if (token == NULL)
		exit(1);
}

//debug
int main(int ac, char **av, char **envp)
{
	t_cmd	*res;
	char	*input = "echo hogehoge > file1 > file2 > file3";

	res = parser(input);
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

