/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 13:19:05 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/21 01:01:52 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		try_expand(char **str, t_envp *env_list);
static void		do_expand(char **str, t_envp *env_list, size_t *i);

void	expand_env(t_list *token, t_envp *env_list)
{
	t_list	*now_token;

	now_token = token;
	while (now_token != NULL)
	{
		try_expand(&(now_token->content), env_list);
		now_token = now_token->next;
	}
}

static void	try_expand(char **str, t_envp *env_list)
{
	int		fg_expand;
	int		fg_parse_single_quote;
	size_t	i;

	fg_parse_single_quote = 1;
	fg_expand = 1;
	i = 0;
	while ((*str)[i] != 0x00)
	{
		if ((*str)[i] == '\"')
			fg_parse_single_quote = !fg_parse_single_quote;
		else if ((*str)[i] == '\'' && fg_parse_single_quote)
			fg_expand = !fg_expand;
		else if ((*str)[i] == '$' && fg_expand)
			do_expand(str, env_list, &i);
		++i;
	}
}

static void	do_expand(char **str, t_envp *env_list, size_t *i)
{
	size_t	envname_tail_i;
	char	*env_name;
	char	*env_value;

	envname_tail_i = *i + get_envname_tail_index(*str + *i);
	env_name = get_env_name_from_token(*str);
	env_value = ft_getenv(env_name, env_list);
	*i = ft_strreplace(str, env_value, *i, envname_tail_i);
	free(env_name);
}
/*
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
*/
