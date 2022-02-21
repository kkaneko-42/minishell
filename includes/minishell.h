/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:50:37 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/21 14:29:50 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# define META_CHAR "><|"
# define NOT_FOUND NULL

typedef struct s_cmd
{
    char            *name;
    t_list          *args;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}               t_cmd;

#endif
