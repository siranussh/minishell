/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:24:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/15 17:51:32 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	execute_pipeline(t_cmd *cmds, t_env *env)
{
	int		i;
	int		pipe_fd[2];
	int		prev_fd;
	int		pid;
	int		status;
	char	*path;
	char	*env_arr;
	t_cmd	*curr;

	status = 0;
	prev_fd = -1;
	curr = cmds;
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
				get_heredoc(curr);
			else if (curr->infile)
				curr->fd_in = open(curr->infile, O_RDONLY);
			else if (prev_fd != -1)
				curr->fd_in = prev_fd;
			else
				curr->fd_in = STDIN_FILENO;
			if (curr->outfile)
			{
				if (curr->append = 1)
					curr->fd_out = open(curr->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				else if (curr->append = 2)
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
				status = run_buil_in(args_count(curr->cmd_line), curr->cmd_line, env);
				exit(status);
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
			if (prev_fd != -1)
				close(prev_fd);
			if (curr->next)
				close(pipe_fd[1]);
		curr = curr->next;
	}
}
