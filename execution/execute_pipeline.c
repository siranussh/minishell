/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:23:57 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/25 23:50:34 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	setup_child_pipes_and_redirs(t_cmd *cmd, int prev_fd, int pipe_fd[2])
{
	setup_signals(0);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	else if (cmd->fd_in != -1)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}	
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	setup_redirs(cmd);
}

static void	close_pipe_fds(int pipe_fd[2])
{
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (pipe_fd[1] != -1)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

int	is_directory(char *path)
{
	DIR	*dir;
	
	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

int child_process(t_cmd *cmd, t_pipe *p,  t_data *data, int pipe_fd[])
{
	int pid;
	
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		setup_child_pipes_and_redirs(cmd, p->prev_fd, pipe_fd);
		close_pipe_fds(pipe_fd);
		if (is_directory(cmd->tokens[0]))
		{
			print_error("minishell", cmd->tokens[0], "Is a directory");
			exit(126);
		}
		if (is_built_in(cmd->tokens))
		{
			p->exit_code = run_built_in(args_count(cmd->tokens),
					cmd->tokens, data);
			exit(p->exit_code);
		}
		execute_single_command(cmd->tokens, data);
		exit(127);
	}
	return (pid);
}

void	execute_pipeline(t_cmd *cmds, t_data * data, t_pipe *p)
{
	t_cmd	*curr;
	int		pipe_fd[2];
	int		i;
	
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	curr = cmds;
	i = 0;
	while (curr)
	{
		setup_pipe(curr, pipe_fd);
		p->pids[i] = child_process(curr, p, data, pipe_fd);
		close_fds(p, pipe_fd);
		curr = curr->next;
		i++;
	}
	if (p->prev_fd != -1)
		close(p->prev_fd);
	wait_for_children(p);
	free(p->pids);
}
