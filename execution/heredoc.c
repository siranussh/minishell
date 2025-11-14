/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:07:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/14 22:10:13 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

static void	get_heredoc_check(int write_end, char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(delim, line) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, write_end);
		free(line);
	}
}

void	get_heredoc(t_cmd *cmds)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	get_heredoc_check(fd[1], cmds->delimiter);
	close(fd[1]);
	cmds->fd_in = fd[0];
}

void	handle_heredocs(t_cmd *cmds)
{
	t_cmd	*curr = cmds;
	t_redir	*r;

	while (curr)
	{
		r = curr->redirs;
		while (r)
		{
			if (r->type == 2)
				get_heredoc(curr);
			r = r->next;
		}
		curr = curr->next;
	}
}
