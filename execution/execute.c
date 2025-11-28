/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:30:37 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/29 00:07:30 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

static void	prepare_all_commands(t_cmd *cmds)
{
	while (cmds)
	{
		parse_redirs(cmds);
		cmds = cmds->next;
	}
}

static void handle_all_heredocs(t_cmd *cmds)
{
	while (cmds)
	{
		process_all_heredocs(cmds);
		cmds = cmds->next;
	}
}

void	execute(t_cmd *cmds, t_data *data, t_pipe *p)
{
	// int		exit_code;
	if (p->cmds_count > 1024)
	{
		print_error("minishell", NULL, "syntax error near unexpected token `|'");
		set_status(2);
		free_data(data);////freeee
		return ;
	}
	prepare_all_commands(cmds);
	handle_all_heredocs(cmds);
	if (only_builtin(cmds, data) != -1)
	{
		free(p->pids);
		// return (get_status());
		return ;
	}
	execute_pipeline(cmds, data, p);
	// if (p->prev_fd != -1)
	// 	close(p->prev_fd);
	// wait_for_children(p);
	// free(p->pids);
	// return (get_status());
}
