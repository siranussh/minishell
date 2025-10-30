/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:07:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/30 16:30:37 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
