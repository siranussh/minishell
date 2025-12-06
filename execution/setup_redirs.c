/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:05:38 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/04 21:07:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

static int	setup_in_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	(void)cmd;
	if (r->type == REDIR_IN)
	{
		if (check_access(r->filename) == 0)
		{
			fd = open(r->filename, O_RDONLY);
			if (fd < 0)
			{
				print_error("minishell", r->filename, "No such file or directory");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
			return (1);
		}
		return (-1);
	}
	return (0);
}

static int	setup_heredoc_redir(t_cmd *cmd, t_redir *r)
{
	if (r->type == REDIR_HEREDOC)
	{
		if (cmd->fd_in != -1)
		{
			dup2(cmd->fd_in, STDIN_FILENO);
			close(cmd->fd_in);
		}
		return (1);
	}
	return (0);
}

static int	setup_out_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	(void)cmd;
	if (r->type == REDIR_OUT)
	{
		if (check_access(r->filename) == 0)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				print_error("minishell", r->filename, "No such file or directory");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
			return (1);
		}
		return (-1);
	}
	return (0);
}

static int	setup_append_redir(t_redir *r, t_cmd *cmd)
{
	int	fd;

	(void)cmd;
	if (r->type == REDIR_APPEND)
	{
		if (check_access(r->filename) == 0)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				print_error("minishell", r->filename, "No such file or directory");
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close (fd);
			return (1);
		}
		return (-1);
	}
	return (0);
}

// int	setup_redirs(t_data *data)
// {
// 	t_redir	*r;

// 	if (!data->cmd || !data->cmd->redirs)
// 		return (1); // No redirs, success
// 	r = data->cmd->redirs;
// 	while (r)
// 	{
// 		if (setup_in_redir(r, data) == -1
// 			|| setup_heredoc_redir(data->cmd, r) == -1
// 			|| setup_out_redir(r, data) == -1
// 			|| setup_append_redir(r, data) == -1)
// 		{
// 			return (-1); // On any error, stop and return -1
// 		}
// 		r = r->next;
// 	}
// 	return (1); // Success
// }
int	setup_redirs(t_cmd *cmd)
{
	t_redir	*r;

	if (!cmd || !cmd->redirs)
		return (1);
	r = cmd->redirs;
	while (r)
	{
		if (setup_in_redir(r, cmd) == -1
			|| setup_heredoc_redir(cmd, r) == -1
			|| setup_out_redir(r, cmd) == -1
			|| setup_append_redir(r, cmd) == -1)
		{

			return (-1);
		}
		r = r->next;
	}
	return (1);
}
