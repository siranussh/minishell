/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 13:53:01 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:06:46 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_data	*get_heredoc_data(t_data *data, int set)
{
	static t_data	*stored = NULL;

	if (set)
		stored = data;
	return (stored);
}

static void	heredoc_sighandler(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_heredoc_data(NULL, 0);
	if (data)
		free_data(data);
	exit(130);
}

void	read_heredoc_child(int write_end, char *delimiter, int quoted,
	t_data *data)
{
	char	*line;

	get_heredoc_data(data, 1);
	signal(SIGINT, heredoc_sighandler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			free_data(data);
			exit(130);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			free_data(data);
			exit(0);
		}
		if (!quoted)
			line = replace_all_val(line, data);
		ft_putendl_fd(line, write_end);
		free(line);
	}
}
