/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:33:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:50:51 by anavagya         ###   ########.fr       */
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

static void	read_heredoc(t_cmd *cmd, char *delimiter)
{
	int	fd[2];
	int	pid;
	int	status;

	if (pipe(fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		close(fd[0]);
		close(fd[1]);
		return ;
	}
	if (pid == 0)
	{
		setup_signals(0);
		close(fd[0]);
		read_heredoc_child(fd[1], delimiter);
		close(fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(fd[0]);
		cmd->fd_in = -1;
		return ;
	}
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd[0];
}

void	process_all_heredocs(t_cmd *cmds)
{
	t_redir	*r;

	r = cmds->redirs;
	while (r)
	{
		if (r->type == REDIR_HEREDOC && r->filename)
			read_heredoc(cmds, r->filename);
		r = r->next;
	}
}
