/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/18 21:30:47 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	execute_one_command(t_cmd *curr, t_pipe *p, t_data *data)
{
	int	pipe_fd[2];
	int	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (curr->next && pipe(pipe_fd) == -1)
		perror("pipe");
	if (!curr->next && is_built_in(curr->tokens))
	{
		p->exit_code = run_built_in(args_count(curr->tokens), curr->tokens, data);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		setup_signals(0);
		child_process(curr, p, data, pipe_fd);
		exit(1);
	}
	else
		parent_process(p, curr, pid, pipe_fd);
}

int	execute(t_cmd *cmds, t_data *data, t_pipe *p)
{
	int		exit_code;
	t_cmd	*curr;

	// curr = cmds;
	// while (curr)
	// {
	// 	parse_redirections(curr);
	// 	curr = curr->next;
	// }
	// handle_heredocs(cmds);
	p->index = 0;
	p->prev_fd = -1;
	curr = cmds;
	while (curr)
	{
		parse_redirections(curr);
		build_redir_list(curr);
		handle_heredocs(curr);
		execute_one_command(curr, p, data);
		p->index++;
		curr = curr->next;
	}
	exit_code = wait_for_children(p);
	return (exit_code);
}
