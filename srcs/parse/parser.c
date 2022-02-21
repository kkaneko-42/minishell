/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 14:16:56 by kkaneko           #+#    #+#             */
/*   Updated: 2022/02/21 20:01:58 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	validate_token(const t_list *token);

t_cmd	*parser(const char *input)
{
	t_list	*token;
	t_cmd	*res;

	token = lexer(input);
	validate_token(token);
	while (token != NULL)
	{
		token = token->next;
	}
	return (res);
}

static void	validate_token(const t_list *token)
{
	//if tokens have some errors, exit
	return (0);
}

int main(int ac, char **av, char **envp)
{
	parser(av[1]);
	return (0);
}