/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 22:28:47 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:45:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	parse_redirs(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->tokens)
		return ;
	while (cmd->tokens[i])
	{
		if (strcmp(cmd->tokens[i], "<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_IN, cmd->tokens[i + 1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_HEREDOC, cmd->tokens[i + 1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_OUT, cmd->tokens[i + 1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_APPEND, cmd->tokens[i + 1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		i++;
	}
}

void	setup_redirs(t_cmd *cmd)
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
