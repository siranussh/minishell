/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:28:16 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:02:33 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

//*************//
//*    NEW    *//
//*************//

static void	prepare_all_commands(t_cmd *cmds)
{
	while (cmds)
	{
		parse_redirs_new(cmds);
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
	// t_cmd	*curr;
	// curr = cmds;
	// p->pids = NULL;
	if (p->cmds_count > 1024)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		set_status(2);
		return ;
	}
	prepare_all_commands(cmds);
	handle_all_heredocs(cmds);
	// p->pids = malloc(sizeof(int) * curr->num_tokens);
	// if (!p->pids)
		// return ;
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
