/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:05:42 by sihakoby          #+#    #+#             */
/*   Updated: 2025/06/14 18:35:21 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static t_data	start_init(void)
{
	t_data	data;

	data.envp = NULL;
	data.ac = -1;
	data.av = NULL;
	data.heredoc = 0;
	data.fd_in = -1;
	data.fd_out = -1;
	data.pipe = NULL;
	data.nb_cmds = -1;
	data.child = -1;
	data.pids = NULL;
	data.cmd_options = NULL;
	data.cmd_path = NULL;
	return (data);
}

static void	generate_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds - 1)
	{
		if (pipe(data->pipe + 2 * i) == -1)
			error_bonus(error_msg_bonus("Could not create pipe", "", "", 1),
				data);
		i++;
	}
}

t_data	init_bonus(int ac, char **av, char **envp)
{
	t_data	data;

	data = start_init();
	data.envp = envp;
	data.ac = ac;
	data.av = av;
	if (!ft_strncmp("here_doc", av[1], 9))
		data.heredoc = 1;
	get_input_file_bonus(&data);
	get_output_file_bonus(&data);
	data.nb_cmds = ac - 3 - data.heredoc;
	data.pids = malloc(sizeof * data.pids * data.nb_cmds);
	if (!data.pids)
		error_bonus(error_msg_bonus("PID error", strerror(errno), "", 1),
			&data);
	data.pipe = malloc(sizeof * data.pipe * 2 * (data.nb_cmds - 1));
	if (!data.pipe)
		error_bonus(error_msg_bonus("Pipe error", "", "", 1), &data);
	generate_pipes(&data);
	return (data);
}
