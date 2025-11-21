/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:28:16 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/21 20:30:17 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

//*************//
//*    NEW    *//
//*************//

static void prepare_all_commands(t_cmd *cmds)
{
	while (cmds)
	{
		parse_redirs_new(cmd, 0);
		// if (!cmds->cmd)
		// 	parse_redirs_new(cmds, 1);
		// else
		// 	parse_redirs_new(cmds, 0);
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

void	execute_new(t_cmd *cmds, t_data *data, t_pipe *p)
{
	// int		exit_code;
	t_cmd	*curr;

	p->prev_fd = -1;
	curr = cmds;
	p->pids = NULL;
	prepare_all_commands(cmds);
	handle_all_heredocs(cmds);
	p->pids = malloc(sizeof(int) * curr->num_tokens);
	if (!p->pids)
		return ;
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
