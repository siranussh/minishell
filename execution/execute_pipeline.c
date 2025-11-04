/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/04 13:02:16 by sihakoby         ###   ########.fr       */
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
	if (!curr->next && is_built_in(curr->tokens))
	{
		p->exit_code = run_built_in(args_count(curr->tokens), curr->tokens, env);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		setup_signals(0);
		child_process(curr, p, env, pipe_fd);
		exit(1);
	}	
	else
		parent_process(p, curr, pid, pipe_fd);
}

int	execute_pipeline(t_cmd *cmds, t_env *env, t_pipe *p)
{
	int		exit_code;
	t_cmd	*curr;

	curr = cmds;
	handle_heredocs(cmds);
	p->index = 0;//new ani
	p->prev_fd = -1;//new ani
	while (curr)
	{
		execute_one_command(curr, p, env);
		p->index++;
		curr = curr->next;
	}
	exit_code = wait_for_children(p);
	return (exit_code);
}
