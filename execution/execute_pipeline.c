/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/15 23:19:00 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

static int	wait_for_children(t_cmd *cmds, t_pipe *p)
{
	int		status;
	int		exit_code;
	pid_t	waited_pid;

	if (cmds->fd_in != -1)
		close(cmds->fd_in);
	if (cmds->fd_out != -1)
		close(cmds->fd_out);
	while (cmds)
	{
		waitpid(p->pids[p->child], &status, 0);
		if (waited_pid == p->pids[p->nb_cmds - 1])
		{
			if ((p->child == (p->nb_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		cmds = cmds->next;
	}
	free(p->pipe);
	free(p->pids);
	return (exit_code);
}

int	execute_pipeline(t_cmd *cmds, t_env *env)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	int		pid;
	int		exit_code;
	char	*path;
	char	**env_arr;
	t_cmd	*curr;
	t_cmd	*tmp;

	exit_code = 0;
	prev_fd = -1;
	curr = cmds;
	tmp = cmds;
	while (tmp)
	{
		if (tmp->heredoc)
			get_heredoc(tmp);
		tmp = tmp->next;
	}
	while (curr)
	{
		if (curr->next && pipe(pipe_fd)== -1)
			perror("pipe");
		pid = fork();
		if (pid == -1)
			perror("fork");
		else if (pid ==0)
		{
			if (curr->heredoc)
			{
				curr->fd_in = open(".heredoc.tmp", O_RDONLY);
				if (fd_in == -1)
					perror("open heredoc");
				dup2(curr->fd_in, STDIN_FILENO);
				close(curr->fd_in);
			}
			else if (curr->infile)
				curr->fd_in = open(curr->infile, O_RDONLY);
			else if (prev_fd != -1)
				curr->fd_in = prev_fd;
			else
				curr->fd_in = STDIN_FILENO;
			if (curr->outfile)
			{
				if (curr->append == 1)
					curr->fd_out = open(curr->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (curr->append == 2)
					curr->fd_out = open(curr->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else if (curr->next)
			{
				curr->fd_out = pipe_fd[1];
			}
			else
				curr->fd_out = STDOUT_FILENO;
			if (is_built_in(curr->cmd_line))
			{
				exit_code = run_built_in(args_count(curr->cmd_line), curr->cmd_line, env);
				exit(exit_code);
			}
			path = find_cmd_path(curr->cmd_line[0], env);
			if (!path)
				return (127);
			env_arr = env_to_array(env);
			execve(path, curr->cmd_line, env_arr);
			perror("execve");
			exit(1);
		}
		else
		{
			if (prev_fd != -1)
				close(prev_fd);
			if (curr->next)
				close(pipe_fd[1]);
			if (curr->next)
				prev_fd = pipe_fd[0];
			else
				prev_fd = -1;
			// close unused ends of the pipe
		}
		curr = curr->next;
	}
	exit_code = wait_for_children(cmds, p);//// I will add a new structure
	if (access(".heredoc.tmp", F_OK) == 0)
		unlink(".heredoc.tmp");
	return (exit_code);
}
