/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:05:30 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:05:30 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_heredoc_child(int fd[2], char *delimiter, int quoted,
	t_data *data)
{
	close(fd[0]);
	read_heredoc_child(fd[1], delimiter, quoted, data);
	close(fd[1]);
	free_data(data);
	exit(0);
}

static int	handle_heredoc_parent(t_data *data, t_cmd *cmd, int fd[2], int pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_signal_nmb = WEXITSTATUS(status);
		return (1);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(fd[0]);
		cmd->fd_in = -1;
		data->exit_code = 130;
		return (0);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	data->exit_code = 128 + WTERMSIG(status);
	return (1);
}

static int	read_heredoc(t_cmd *cmd, t_redir *r, t_data *data)
{
	int	fd[2];
	int	pid;
	int	result;

	if (pipe(fd) == -1)
		return (perror("minishell: pipe"), 0);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		set_default_signals();
		handle_heredoc_child(fd, r->filename, r->quoted_delimiter, data);
	}
	result = handle_heredoc_parent(data, cmd, fd, pid);
	setup_signals();
	if (!result)
		return (0);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd[0];
	return (1);
}

int	process_all_heredocs(t_cmd *cmds, t_data *data)
{
	t_redir	*r;

	r = cmds->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
		{
			if (!read_heredoc(cmds, r, data))
				return (0);
		}
		r = r->next;
	}
	return (1);
}
