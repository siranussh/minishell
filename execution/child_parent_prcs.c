/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_parent_prcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:11:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/23 13:11:53 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(t_cmd *curr, t_pipe *p, t_env *env, int pipe_fd[])
{
	// char	*path;

	setup_input(curr, p->prev_fd);
	setup_output(curr, pipe_fd);
	if (is_built_in(curr->cmd_line))
	{
		p->exit_code = run_built_in(args_count(curr->cmd_line),
				curr->cmd_line, env);
		exit(p->exit_code);
	}
	execute_single_command(curr->cmd_line, env);
	// path = find_cmd_path(curr->cmd_line[0], env);
	// if (!path)
	// 	exit(127);
	// p->env_arr = env_to_array(env);
	// execve(path, curr->cmd_line, p->env_arr);
	// perror("execve");
	dup2_and_close(curr->fd_in, STDIN_FILENO);
	dup2_and_close(curr->fd_out, STDOUT_FILENO);
	// free(path);
	// ft_free(p->env_arr);
	exit(1);
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
