/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:04:00 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/19 22:09:30 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

//************ *//
//*    NEW     *//
//************ *//

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

static void read_heredoc(t_cmd *cmd, char *delimiter)
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

void	parse_redirs_builtin(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->tokens)
		return ;
	while (cmd->tokens[i])
	{
		if (strcmp(cmd->tokens[i], "<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_IN, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_HEREDOC, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_OUT, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_APPEND, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		i++;
	}
}

void	setup_redirs_builtin(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == REDIR_IN)
		{
			fd = open(r->filename, O_RDONLY);
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", r->filename);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == REDIR_HEREDOC)
		{
			if (cmd->fd_in != -1)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
			}
		}
		else if (r->type == REDIR_OUT)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", r->filename);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close (fd);
		}
		else if (r->type == REDIR_APPEND)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				printf("minishell: %s: No such file or directory\n", r->filename);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close (fd);
		}
		r = r->next;
	}
}

int	only_builtin(t_cmd *cmd, t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_code;

	if (!is_built_in(cmd->tokens) || ft_cmd_size(cmd) != 1)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	parse_redirs_builtin(cmd);
	process_all_heredocs(cmd);
	setup_redirs_builtin(cmd);
	exit_code = run_built_in(args_count(cmd->tokens),
			cmd->tokens, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	set_status(exit_code);
	return (exit_code);
}
