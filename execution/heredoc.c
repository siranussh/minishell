/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:07:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/15 22:46:44 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

static void	get_heredoc_check(int fd, char *delim)
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
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	get_heredoc(t_cmd *cmds)
{
	int	tmp_fd;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp_fd == -1)
		perror("open");
	get_heredoc_check(tmp_fd, cmds->delimiter);
	close(tmp_fd);
}

