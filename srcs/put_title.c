/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_title.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:42:58 by kkaneko           #+#    #+#             */
/*   Updated: 2022/03/24 00:59:19 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	printf_with_color(const char *str, const char *color);

void	put_title(void)
{
	printf_with_color(" __  __ _       _     _          _ _ \n", CYAN);
	printf_with_color("|  \\/  (_)_ __ (_)___| |__   ___| | |\n", CYAN);
	printf_with_color("| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |\n", CYAN);
	printf_with_color("| |  | | | | | | \\__ \\ | | |  __/ | |\n", CYAN);
	printf_with_color("|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|\n", CYAN);
	printf("\n");
}

static void	printf_with_color(const char *str, const char *color)
{
	printf("%s%s%s", color, str, COLOR_RESET);
}
