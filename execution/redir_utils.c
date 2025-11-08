/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:49:17 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/08 13:49:17 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_redir_type(char *token)
{
	if (!token)
		return (-1);
	if (ft_strcmp(token, "<") == 0)
		return (1);
	else if (ft_strcmp(token, "<<") == 0)
		return (2);
	else if (ft_strcmp(token, ">") == 0)
		return (3);
	else if (ft_strcmp(token, ">>") == 0)
		return (4);
	return (-1);
}

void	add_redir_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	setup_redirections(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redirs;
	while (r)
	{
		if (r->type == 1)
		{
			fd = open(r->filename, O_RDONLY);
			if (fd < 0)
				perror(r->filename);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == 2)
		{
			if (cmd->fd_in != -1)
			{
				dup2(cmd->fd_in, STDIN_FILENO);
				close(cmd->fd_in);
			}
		}
		else if (r->type == 3)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror(r->filename);
			dup2(fd, STDOUT_FILENO);
			close (fd);
		}
		else if (r->type == 4)
		{
			fd = open(r->filename,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror(r->filename);
			dup2(fd, STDOUT_FILENO);
			close (fd);
		}
		r = r->next;
	}
}

void	build_redir_list(t_cmd *cmd)
{
	if (cmd->infile)
		add_redir_back(&cmd->redirs, init_redir(1, cmd->infile));
	if (cmd->heredoc && cmd->delimiter)
		add_redir_back(&cmd->redirs, init_redir(2, cmd->delimiter));
	if (cmd->outfile)
	{
		if (cmd->append == 2)
			add_redir_back(&cmd->redirs, init_redir(4, cmd->outfile));
		else
			add_redir_back(&cmd->redirs, init_redir(3, cmd->outfile));
	}
}
