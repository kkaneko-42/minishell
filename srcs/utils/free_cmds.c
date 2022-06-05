/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaneko <kkaneko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 01:03:58 by kkaneko           #+#    #+#             */
/*   Updated: 2022/06/04 18:02:08 by kkaneko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd_members(t_cmd *cmd);

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*now;
	t_cmd	*next;

	now = cmds;
	while (now != NULL)
	{
		next = now->next;
		free_cmd_members(now);
		now = next;
	}
}

static void	free_cmd_members(t_cmd *cmd)
{
	free(cmd->name);
	ft_lstclear(&(cmd->args), free_content);
	ft_lstclear(&(cmd->heredoc_end), free_content);
	free(cmd->stdin_str);
	if (cmd->fd_out > STDERR_FILENO)
		close(cmd->fd_out);
	free(cmd);
}
