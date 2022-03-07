/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:19:05 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/07 18:30:17 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		try_expand(char **str, t_envp *env_list);
static void		do_expand(char **str, t_envp *env_list);
static char		*get_env_name_from_token(char *str);
static size_t	get_envname_tail_index(char *str);
static size_t	get_envname_head_index(char *str);

void	expand_env(t_list *token, t_envp *env_list)
{
	t_list	*now_token;

	now_token = token;
	while (now_token != NULL)
	{
		if (now_token->content[0] != '\''
			&& ft_strchr(now_token->content, '$') != NOT_FOUND)
		{
			do_expand(&(now_token->content), env_list);
		}
		now_token = now_token->next;
	}
}

static void	do_expand(char **str, t_envp *env_list)
{
	size_t	i;
	size_t	envname_tail_i;
	char	*env_name;
	char	*env_value;

	i = 0;
	while ((*str)[i] != 0x00)
	{
		if ((*str)[i] == '$')
		{
			envname_tail_i = i + get_envname_tail_index(*str + i);
			env_name = get_env_name_from_token(*str);
			env_value = ft_getenv(env_name, env_list);
			i = ft_strreplace(str, env_value, i, envname_tail_i);
		}
		++i;
	}
}

static char	*get_env_name_from_token(char *str)
{
	size_t	head_i;
	size_t	tail_i;
	char	*res;

	head_i = get_envname_head_index(str);
	tail_i = get_envname_tail_index(str);
	res = ft_substr(str, head_i, tail_i - head_i + 1);
	return (res);
}

static size_t	get_envname_tail_index(char *str)
{
	size_t	i;

	i = get_envname_head_index(str);
	while (is_snakecase(str[i], i))
		++i;
	return (i - 1);
}

static size_t	get_envname_head_index(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0x00 && str[i] != '$')
		++i;
	return (i + 1);
}

//debug
int main(int ac, char **av, char **envp)
{
	t_envp	*env_list = get_envp_list(envp);
	char	*input = av[1];
	t_list	*token = lexer(av[1]);

	printf("------------before------------\n");
	for (t_list *now_token = token; now_token != NULL; now_token = now_token->next)
		printf("%s\n", now_token->content);
	printf("------------after-------------\n");
	expand_env(token, env_list);
	for (t_list *now_token = token; now_token != NULL; now_token = now_token->next)
		printf("%s\n", now_token->content);
	return (0);
}
