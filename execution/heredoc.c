/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:33:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/30 23:13:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

static void	read_heredoc_child(int write_end, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, write_end);
		free(line);
	}
}

static void	handle_heredoc_child(int fd[2], char *delimiter)
{
	close(fd[0]);
	read_heredoc_child(fd[1], delimiter);
	close(fd[1]);
	exit(0);
}

static int	handle_heredoc_parent(t_cmd *cmd, int fd[2], int pid)
{
	int	status;

	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_exit_code = WEXITSTATUS(status);
		return (1);
	}
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		close(fd[0]);
		cmd->fd_in = -1;
		g_exit_code = 130;
		return (0);
	}
	else if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19);
	g_exit_code = 128 + WTERMSIG(status);
	return (1);
}

static int	read_heredoc(t_cmd *cmd, char *delimiter)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
		return (perror("minishell: pipe"), 0);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (perror("minishell: fork"), 0);
	}
	if (pid == 0)
	{
		set_default_signals();
		handle_heredoc_child(fd, delimiter);
	}
	if (!handle_heredoc_parent(cmd, fd, pid))
		return (0);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd[0];
	return (1);
}

int	process_all_heredocs(t_cmd *cmds)
{
	t_redir	*r;

	r = cmds->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC)
		{
			if (!read_heredoc(cmds, r->filename))
				return (0);
		}
		r = r->next;
	}
	return (1);
}
