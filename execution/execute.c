/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:58:50 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:58:50 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	execute(t_cmd *cmds, t_data *data, t_pipe *p)
{
	if (p->cmds_count > 1024)
	{
		print_error("minishell", NULL,
			"syntax error near unexpected token `|'");
		return (2);
	}
	prepare_all_commands(cmds);
	if (!handle_all_heredocs(cmds, data))
		return (1);
	data->exit_code = only_builtin(cmds, data);
	if (data->exit_code != -1)
		return (data->exit_code);
	data->exit_code = execute_pipeline(cmds, data, p);
	return (data->exit_code);
}
