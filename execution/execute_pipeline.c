/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/22 18:23:37 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

t_pipe	*init_pipe_struct(t_cmd *cmds)
{
	t_pipe	*p;

	p = (t_pipe *)malloc(sizeof(t_pipe));
	if (!p)
		return (NULL);
	p->fd_in = -1;
	p->fd_out = -1;
	// p->nb_cmds = -1;
	// p->child = -1;
	p->prev_fd = -1;
	p->exit_code = 0;
	p->cmds_count = ft_cmd_size(cmds);
	p->pids = (int *)malloc(sizeof(int) * p->cmds_count);
	if (!p->pids)
	{
		free(p);
		return (NULL);//or smth else
	}
	return (p);
}

void	handle_heredocs(t_cmd *cmds)
{
	t_cmd *tmp = cmds;

	while (tmp)
	{
		if (tmp->heredoc)
			get_heredoc(tmp);
		tmp = tmp->next;
	}
}

int	wait_for_children(t_pipe *p)
{
	int		i;
	int		status;
	int		exit_code;
	pid_t	waited_pid;

	exit_code = 0;
	// if (cmds->fd_in != -1)
	// 	close(cmds->fd_in);
	// if (cmds->fd_out != -1)
	// 	close(cmds->fd_out);
	i = 0;
	while (i < p->cmds_count)
	{
		waitpid(p->pids[i], &status, 0);
		if (i == (p->cmds_count - 1) && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	free(p->pids);
	return (exit_code);
}

void	setup_input(t_cmd *curr, int prev_fd)
{
	if (curr->heredoc && curr->fd_in != -1)
	{
		dup2(curr->fd_in, STDIN_FILENO);
		close(curr->fd_in);
	}
	else if (curr->infile)
	{
		curr->fd_in = open(curr->infile, O_RDONLY);
		if (curr->fd_in == -1)
			perror("open infile");
		if (curr->fd_in != STDIN_FILENO)
		{
			dup2(curr->fd_in, STDIN_FILENO);
			close(curr->fd_in);
		}
	}
	else if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
}

void	setup_output(t_cmd *curr, int pipe_fd[])
{
	if (curr->outfile)
	{
		if (curr->append == 1)
			curr->fd_out = open(curr->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (curr->append == 2)
			curr->fd_out = open(curr->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (curr->fd_out == -1)
			perror("open outfile");
		if (curr->fd_out != STDOUT_FILENO)
		{
			dup2(curr->fd_out, STDOUT_FILENO);
			close(curr->fd_out);
		}
	}
	else if (curr->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
}

void	child_process(t_cmd *curr, t_pipe *p, t_env *env, int pipe_fd[])
{
	char	*path;

	setup_input(curr, p->prev_fd);
	setup_output(curr, pipe_fd);
	if (is_built_in(curr->cmd_line))
	{
		p->exit_code = run_built_in(args_count(curr->cmd_line), curr->cmd_line, env);
		exit(p->exit_code);
	}
	path = find_cmd_path(curr->cmd_line[0], env);
	if (!path)
		exit(127);
	p->env_arr = env_to_array(env);
	execve(path, curr->cmd_line, p->env_arr);
	perror("execve");
	if (curr->fd_in != STDIN_FILENO)
	{
		dup2(curr->fd_in, STDIN_FILENO);
		close(curr->fd_in);
	}
	if (curr->fd_out != STDOUT_FILENO)
	{
		dup2(curr->fd_out, STDOUT_FILENO);
		close(curr->fd_out);
	}
	exit(1);
}

void	parent_process(t_pipe *p, t_cmd *curr, int pid, int pipe_fd[], int i)
{
	p->pids[i] = pid;
	if (p->prev_fd != -1)
		close(p->prev_fd);
	if (curr->next)
		close(pipe_fd[1]);
	if (curr->next)
		p->prev_fd = pipe_fd[0];
	else
		p->prev_fd = -1;
	// close unused ends of the pipe
}

void	execute_one_command(t_cmd *curr, t_pipe *p, t_env *env, int i)
{
	int	pipe_fd[2];
	int	pid;

	if (curr->next && pipe(pipe_fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
		child_process(curr, p, env, pipe_fd);
	else
		parent_process(p, curr, pid, pipe_fd, i);
}

int	execute_pipeline(t_cmd *cmds, t_env *env, t_pipe *p)
{
	int		i;
	int		exit_code;
	t_cmd	*curr;

	i = 0;
	curr = cmds;
	handle_heredocs(cmds);
	while (curr)
	{
		execute_one_command(curr, p, env, i);
		i++;
		curr = curr->next;
	}
	exit_code = wait_for_children(p);
	if (access(".heredoc.tmp", F_OK) == 0)
		unlink(".heredoc.tmp");
	return (exit_code);
}
