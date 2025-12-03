/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:30:37 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/30 22:17:47 by anavagya         ###   ########.fr       */
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

static int	handle_all_heredocs(t_cmd *cmds, t_data *data)
{
	while (cmds)
	{
		if (!process_all_heredocs(cmds, data))
			return (0);
		cmds = cmds->next;
	}
	return (1);
}

void	execute(t_cmd *cmds, t_data *data, t_pipe *p)
{
	if (p->cmds_count > 1024)
	{
		print_error("minishell", NULL,
			"syntax error near unexpected token `|'");
		set_status(2);
		free_data(data);
		return ;
	}
	prepare_all_commands(cmds);
	if (!handle_all_heredocs(cmds, data))
		return ;
	if (only_builtin(cmds, data) != -1)
	{
		return ;
	}
	execute_pipeline(cmds, data, p);
}
