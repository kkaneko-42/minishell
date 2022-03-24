/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:50:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/25 00:17:37 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# define CYAN "\x1b[36m"
# define GREEN "\x1b[32m"
# define COLOR_RESET "\x1b[39m"
# define HEREDOC_PROMPT "heredoc> "
# define INIT NULL
# define NOT_FOUND NULL
# define PARSE_ERR "parse error\n"
# define INIT_ERR "Initalization error\n"
# define SHELL_NAME "\x1b[32mminishell$ \x1b[39m"
# define EXIT_MSG "exit\n"
# define LLONG_MAX_STR "9223372036854775807"
# define LLONG_MIN_STR "-9223372036854775808"
# define FORK_ERR -1
# define WAIT_ERR -1
# define CMD_SUCCESS 0
# define CMD_ERR 1

typedef struct s_cmd
{
	char			*name;
	t_list			*args;
	char			*stdin_str;
	int				fd_out;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*content;
	int				rank;
}					t_envp;

t_list	*lexer(const char *input);
t_cmd	*parser(const char *input, t_envp *env_list);
void	expand_env(t_list *token, t_envp *env_list);

void	exec(t_cmd *input, t_envp **envp);
void	echo(t_cmd *input);
int		cd(t_cmd *input, t_envp *envp);
int		pwd(t_cmd *input);
int		export(t_cmd *input, t_envp *envp);
int		env(t_cmd *input, t_envp *envp);
int		unset(t_cmd *input, t_envp **envp);
int		exit_builtin(t_cmd *input);
void	delete_env(t_envp **envp, char *old_env);
char	*get_now_path(void);
void	cd_set_env(t_envp *envp, char *old_path);
int		is_exist_env(t_envp *envp, const char *new_env);
int		is_empty_str(const char *s);
t_envp	*get_envp_list(char **envp);
int		first_char_is_equal(const char *s);
int		forbidden_char_is_exist_in_envp(const char *s);
int		addback_envp_list(t_envp **envp_list, char *s);
int		ft_strcmp(char *s1, char *s2);
int		get_max_rank(t_envp *envp);
void	free_strs(char **strs);
int		too_many_args_err(char *cmd_name);
void	num_arg_required_err(char *exit_status);
int		identifier_err(char *cmd_name, char *content);
int		cd_err(t_cmd *input);
int		pwd_err(void);
void	do_exexve(t_cmd *input, t_envp *envp);
void	no_file_dir_err(char *cmd_name);
void	cmd_not_found_err(char *cmd_name);
char	*three_strjoin(char *s1, char *s2, char *s3);
t_cmd	*t_cmd_last(t_cmd *input);
int		t_cmd_size(t_cmd *input);
void	set_output(t_cmd *input, int fd[2], int from_right);
void	set_input_from_redirection(const char *stdin_str);
void	set_input(t_cmd *input, int fd[2], int from_right);
pid_t	fork_and_err(void);
int		waitpid_and_err(pid_t pid);
pid_t	fork_and_waitpid(void);
void	do_pipe(t_cmd *input, t_envp **envp, int n);
int		do_cmd(t_cmd *input, t_envp **envp);
int		is_snakecase(char c, size_t i);
char	*ft_getenv(const char *name, t_envp *env_list);
size_t	ft_strreplace(
			char **str, const char *replace, size_t start, size_t end);
void	receiver(sig_atomic_t sig, void (*handler)(sig_atomic_t));
void	lstdel_head(t_list **top);
void	lstdel_tail(t_list *lst);
void	lstdel_mid(t_list *lst);
void	re_lexer(t_list **src);
void	refact_token(t_list **top);
void	remove_quotes_from_cmds(t_cmd *top);
void	remove_quotes(char **str);
void	ft_lstjoin(t_list **lst1, t_list *lst2);
void	free_content(char *content);
int		is_metachar(const char *str);
void	exit_with_error(const char *msg, int status);
int		check_metachar_target(const t_list *token);
int		check_nb_quotes(const t_list *tokens);
void	free_cmds(t_cmd *cmds);
void	input_file_specify(t_cmd *cmd, t_list **token);
void	heredoc(t_cmd *cmd, t_list **token);
void	output_file_specify(t_cmd *cmd, t_list **token, int fg_append);
void	get_cmd_info(t_cmd *cmd, t_list **token);
void	get_cmd_args(t_cmd *cmd, t_list **token);
t_cmd	*cmd_new(char *name);
void	cmdadd_back(t_cmd **lst, t_cmd *new);
int		validate_token(const t_list *token);
size_t	get_envname_head_index(char *str);
size_t	get_envname_tail_index(char *str);
char	*get_env_name_from_token(char *str);
void	free_envp_list(t_envp **env_list, void (*del)(char *));
int		count_env_lstsize(t_envp *env_list);
void	put_title(void);
void	receiver_for_readline(void);
void	receiver_for_exec(void);

//debug
void	put_all_tokens(t_list *tokens);

#endif
