/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:47:07 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/04 17:20:58 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	receiver_for_readline(void)
{
	receiver(SIGINT, sig_handler_rl);
	receiver(SIGQUIT, SIG_IGN);
}

void	receiver_for_exec(void)
{
	receiver(SIGINT, sig_handler_exec);
	receiver(SIGQUIT, sig_handler_exec);
}
