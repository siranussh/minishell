/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/30 16:30:18 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_one_command(t_cmd *curr, t_pipe *p, t_env *env)
{
	int	pipe_fd[2];
	int	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (curr->next && pipe(pipe_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
		child_process(curr, p, env, pipe_fd);
	else
		parent_process(p, curr, pid, pipe_fd);
}

int	execute_pipeline(t_cmd *cmds, t_env *env, t_pipe *p)
{
	int		exit_code;
	t_cmd	*curr;

	curr = cmds;
	handle_heredocs(cmds);
	while (curr)
	{
		execute_one_command(curr, p, env);
		p->index++;
		curr = curr->next;
	}
	exit_code = wait_for_children(p);
	return (exit_code);
}
