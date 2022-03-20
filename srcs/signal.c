/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:47:07 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/18 16:24:59 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	receiver(void (*handler)(sig_atomic_t))
{
	/* int					err_fg;
	struct sigaction	act;

	err_fg = 0;
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = handler;
	err_fg += sigemptyset(&(act.sa_mask));
	err_fg += sigaction(SIGQUIT, &act, NULL);
	err_fg += sigaction(SIGINT, &act, NULL);
	if (err_fg < 0)
	{
		printf(INIT_ERR);
		exit(1);
	} */
}
