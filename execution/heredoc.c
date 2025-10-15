/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:07:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/15 15:16:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

static void	get_heredoc_check(int fd, int stdin_fd, char *delim)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(stdin_fd);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(delim) + 1
			&& !ft_strncmp(line, delim, ft_strlen(delim))
			&& line[ft_strlen(delim)] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	get_heredoc(t_cmd *cmds)
{
	int	tmp_fd;
	int	stdin_fd;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = STDIN_FILENO;//ft_strdup(STDIN_FILENO);
	if (tmp_fd == -1)
		printf("minishell: I don't know error type");
	get_heredoc_check(tmp_fd, stdin_fd, cmds->delimiter);
	close(tmp_fd);
}

