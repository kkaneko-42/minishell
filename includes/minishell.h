/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:50:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/15 15:07:58 by okumurahyu       ###   ########.fr       */
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
# define SIG_CTRL_C SIGUSR1
# define SIG_BACKSLASH SIGUSR2
# define HEREDOC_PROMPT "heredoc> "
# define INIT NULL
# define NOT_FOUND NULL
# define PARSE_ERR "parse error\n"
# define INIT_ERR "Initalization error\n"
# define SHELL_NAME "minishell$ "
# define EXIT_MSG "exit\n"
# define APPEND 1

typedef struct s_cmd
{
    char            *name;
    t_list          *args;
    int             fd_out;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}                   t_cmd;

typedef struct s_envp
{
    struct s_envp	*next;
	struct s_envp	*prev;
	char			*content;
	int				rank;
}                   t_envp;


t_list	*lexer(const char *input);
t_cmd	*parser(const char *input);

void	exec(t_cmd *input, t_envp **envp);
void	echo(t_cmd *input);
void	cd(t_cmd *input, t_envp *envp);
void	pwd(t_cmd *input);
void	export(t_cmd *input, t_envp *envp);
void	env(t_cmd *input, t_envp *envp);
void	unset(t_cmd *input, t_envp **envp);
void	delete_env_export(t_envp **envp, char *p_args);
int	    is_exist_env(t_envp *envp, char *new_env);
t_envp	*get_envp_list(char **envp);
int	    first_char_is_equal(char *s);
int	    forbidden_char_is_exist_in_envp(char *s);
int	    addback_envp_list(t_envp **envp_list, char *s);
int	    ft_strcmp(char *s1, char *s2);
int	    get_max_rank(t_envp *envp);
void	free_strs(char **strs);
void	do_exexve(t_cmd *input, t_envp *envp);
char	*three_strjoin(char *s1, char *s2, char *s3);
int	    is_snakecase(char c, size_t i);
char	*ft_getenv(const char *name, t_envp *env_list);
size_t  ft_strreplace(
			char **str, const char *replace, size_t start, size_t end);
void	receiver(void (*handler)(sig_atomic_t));

#endif
