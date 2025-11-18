/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:28:16 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/18 22:59:21 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

/************ */
/*    NEW     */
/************ */

int	execute_new(t_cmd *cmds, t_data *data, t_pipe *p)
{
	// int		exit_code;
	// t_cmd	*curr;

	p->index = 0;
	p->prev_fd = -1;
	// curr = cmds;
	if (only_builtin(cmds, data) != -1)
		return (get_status());
	// execute_pipeline(cmds, p, data);
	// wait_for_children(p);
	// execute_one_command(cmds, p, data);
	// exit_code = wait_for_children(p);
	return (get_status());
}