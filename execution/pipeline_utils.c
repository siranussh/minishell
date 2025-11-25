/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:22:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/25 20:54:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	dup2_and_close(int fd1, int fd2)
{
	if (fd1 != fd2)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

int	wait_for_children(t_pipe *p)
{
	int		i;
	int		status;
	int		exit_code;

	exit_code = 0;
	i = 0;
	while (i < p->cmds_count)
	{
		waitpid(p->pids[i], &status, 0);
		if (i == (p->cmds_count - 1) && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	return (exit_code);
}

void	close_fds(t_pipe *p, int pipe_fd[2])
{
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (p->prev_fd != -1)
		close(p->prev_fd);
	p->prev_fd = pipe_fd[0];
}

void	setup_pipe(t_cmd *curr, int pipe_fd[2])
{
	if (curr->next)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
}
