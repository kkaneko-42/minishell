/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:50:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/23 19:59:36 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <readline/readline.h>
# include <readline/history.h>
# define HEREDOC_PROMPT "heredoc> "
# define INIT NULL
# define NOT_FOUND NULL
# define PARSE_ERR "parse error\n"
# define APPEND 1

typedef struct s_cmd
{
    char            *name;
    t_list          *args;
    int             fd_out;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}                   t_cmd;

t_list	*lexer(const char *input);
t_cmd	*parser(const char *input);
void	exec(t_cmd *input);
void	cd(t_cmd *input);
#endif
