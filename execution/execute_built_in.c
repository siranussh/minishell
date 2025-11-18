/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:04:00 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/19 00:08:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

/************ */
/*    NEW     */
/************ */

static void read_heredoc(t_cmd *cmd, char *delimiter, int count)
{
	int fd[2];
	char *line;
	int i = 0;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	while (i < count)
	{
		while (1)
		{
			line = readline("> ");
			if (!line)
				break;
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break;
			}
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
		i++;
	}
	close(fd[1]);
	if (cmd->fd_in != -1)
		close(cmd->fd_in);
	cmd->fd_in = fd[0];
}///////////////////////////////////////

void	process_all_heredocs(t_cmd *cmds)
{
	// t_cmd	*curr;
	t_redir	*r;
	t_redir	*tmp;
	int		count;
	// curr = cmds;
	r = cmds->redirs;
	tmp = r;
	while (tmp)
	{
		if (tmp->type == REDIR_HEREDOC)
			count++;
		tmp = tmp->next;
	}
	while (r)
	{
		if (r->type == REDIR_HEREDOC && r->filename)
			read_heredoc(cmds, r->filename, count);
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
			add_redir_back(&cmd->redirs, init_redir(REDIR_IN, ft_strdup(cmd->tokens[i+1])));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_HEREDOC, ft_strdup(cmd->tokens[i+1])));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		}
		else if (strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_OUT, ft_strdup(cmd->tokens[i+1])));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_APPEND, ft_strdup(cmd->tokens[i+1])));
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
				perror(r->filename);
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
				perror(r->filename);
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
				perror(r->filename);
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
	// if (cmd->next == NULL)
	// {
	// 	dup2(cmd->fd_in, STDIN_FILENO);
	// 	dup2(cmd->fd_out, STDOUT_FILENO);
	// }
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	set_status(exit_code);
	return (exit_code);
}
