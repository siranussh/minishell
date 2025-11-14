/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent_prcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:11:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/14 22:00:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	child_process(t_cmd *curr, t_pipe *p, t_data *data, int pipe_fd[])
{
	setup_redirections(curr);
	setup_input(curr, p->prev_fd);
	setup_output(curr, pipe_fd);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (is_built_in(curr->tokens))
	{
		p->exit_code = run_built_in(args_count(curr->tokens),
				curr->tokens, data);
		exit(p->exit_code);
	}
	execute_single_command(curr->tokens, data);
}

void	parent_process(t_pipe *p, t_cmd *curr, int pid, int pipe_fd[])
{
	p->pids[p->index] = pid;
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (curr->next)
		close(pipe_fd[1]);
	if (curr->next)
		p->prev_fd = pipe_fd[0];
	else
		p->prev_fd = -1;
}
