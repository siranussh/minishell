/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:14:37 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/24 22:28:16 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

static int	setup_in_redir(t_redir *r, t_data *data)
{
	int	fd;

	if (r->type == REDIR_IN)
	{
		check_access(r->filename, data);
		fd = open(r->filename, O_RDONLY);
		if (fd < 0)
		{
			print_error("minishell", r->filename, "No such file or directory");
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (1);
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

static int	setup_out_redir(t_redir *r, t_data *data)
{
	int	fd;

	if (r->type == REDIR_OUT)
	{
		check_access(r->filename, data);
		fd = open(r->filename,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			print_error("minishell", r->filename, "No such file or directory");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		return (1);
	}
	return (0);
}

static int	setup_append_redir(t_redir *r, t_data *data)
{
	int	fd;

	if (r->type == REDIR_APPEND)
	{
		check_access(r->filename, data);
		fd = open(r->filename,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			print_error("minishell", r->filename, "No such file or directory");
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close (fd);
		return (1);
	}
	return (0);
}

void	setup_redirs(t_data *data)
{
	t_redir	*r;

	if (!data->cmd || !data->cmd->redirs)
		return ;
	r = data->cmd->redirs;
	while (r)
	{
		if (setup_in_redir(r, data) || setup_heredoc_redir(data->cmd, r)
			|| setup_out_redir(r, data) || setup_append_redir(r, data))
		{
			r = r->next;
			continue ;
		}
		r = r->next;
	}
}
