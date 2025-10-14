/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_get_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:10 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/14 13:34:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	get_input_file_bonus(t_data *d)
{
	if (d->heredoc == 1)
	{
		get_heredoc(d);
		d->fd_in = open(".heredoc.tmp", O_RDONLY);
		if (d->fd_in == -1)
			error_bonus(error_msg_bonus("here_doc", ": ", strerror(errno),
					1), d);
	}
	else
	{
		d->fd_in = open(d->av[1], O_RDONLY, 644);
		if (d->fd_in == -1)
			error_msg_bonus(strerror(errno), ": ", d->av[1], 1);
	}
}

void	get_output_file_bonus(t_data *d)
{
	if (d->heredoc == 1)
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		d->fd_out = open(d->av[d->ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd_out == -1)
		error_msg_bonus(strerror(errno), ": ", d->av[d->ac - 1], 1);
}

                 /***********************/
/******************      Petq kga       ************************/
static void	get_heredoc_check(int fd, int stdin_fd, t_data *d)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		line = get_next_line(stdin_fd);
		if (!line)
			break ;
		if (ft_strlen(line) == ft_strlen(d->av[2]) + 1
			&& !ft_strncmp(line, d->av[2], ft_strlen(d->av[2]))
			&& line[ft_strlen(d->av[2])] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}
/*******************************************************************/


void	get_heredoc(t_data *d)
{
	int	tmp_fd;
	int	stdin_fd;

	tmp_fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	stdin_fd = STDIN_FILENO;//ft_strdup(STDIN_FILENO);
	if (tmp_fd == -1)
		error_bonus(error_msg_bonus("here_doc", ": ", strerror(errno), 1), d);
	get_heredoc_check(tmp_fd, stdin_fd, d);
	close(tmp_fd);
}
