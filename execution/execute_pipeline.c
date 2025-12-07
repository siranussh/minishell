/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:59:04 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:59:04 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_child_pipes_and_redirs(t_data *data, t_cmd *cmd, int prev_fd,
			int pipe_fd[2])
{
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
	if (cmd->redirs && setup_redirs(cmd) == -1)
	{
		free_data(data);
		exit(1);
	}
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

int	child_process(t_cmd *cmd, t_pipe *p, t_data *data, int pipe_fd[])
{
	int	pid;
	int	exit_code;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
	{
		setup_signals();
		setup_child_pipes_and_redirs(data, cmd, p->prev_fd, pipe_fd);
		close_pipe_fds(pipe_fd);
		exit_code = execute_single_command(cmd->tokens, data);
		free_data(data);
		exit(exit_code);
	}
	return (pid);
}

int	execute_pipeline(t_cmd *cmds, t_data *data, t_pipe *p)
{
	t_cmd	*curr;
	int		pipe_fd[2];
	int		i;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	curr = cmds;
	i = -1;
	setup_signals_parent_exec();
	while (curr)
	{
		if (setup_pipe(curr, pipe_fd) == -1)
		{
			close_pipe_fds(pipe_fd);
			perror("minishell: pipe");
			break ;
		}
		p->pids[++i] = child_process(curr, p, data, pipe_fd);
		close_fds(p, pipe_fd);
		curr = curr->next;
	}
	if (p->prev_fd != -1)
		close(p->prev_fd);
	data->exit_code = wait_for_children(p);
	return (data->exit_code);
}
