/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:06:25 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/11 22:01:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex_bonus.h"

static void	check_io_redirection(int input, int output, t_data *d)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		error_bonus(1, d);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		error_bonus(1, d);
	}
}

static void	execute_child_command(t_data *d)
{
	if (d->child == 0)
		check_io_redirection(d->fd_in, d->pipe[1], d);
	else if (d->child == d->nb_cmds - 1)
		check_io_redirection(d->pipe[2 * d->child - 2], d->fd_out, d);
	else
		check_io_redirection(d->pipe[2 * d->child - 2],
			d->pipe[2 * d->child + 1], d);
	close_fds_bonus(d);
	if (d->cmd_options == NULL || d->cmd_path == NULL)
		error_bonus(1, d);
	if (execve(d->cmd_path, d->cmd_options, d->envp) == -1)
		error_bonus(error_msg_bonus(d->cmd_options[0], ": ",
				strerror(errno), 1), d);
}

static int	wait_for_children(t_data *d)
{
	int		status;
	int		exit_code;
	pid_t	waited_pid;

	close_fds_bonus(d);
	d->child--;
	exit_code = 1;
	while (d->child >= 0)
	{
		waited_pid = waitpid(d->pids[d->child], &status, 0);
		if (waited_pid == d->pids[d->nb_cmds - 1])
		{
			if ((d->child == (d->nb_cmds - 1)) && WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
		}
		d->child--;
	}
	free(d->pipe);
	free(d->pids);
	return (exit_code);
}

static int	execute_pipeline(t_data *d)
{
	int		exit_code;

	if (pipe(d->pipe) == -1)
		error_bonus(error_msg_bonus("pipe", ": ", strerror(errno), 1), d);
	d->child = 0;
	while (d->child < d->nb_cmds)
	{
		d->cmd_options = ft_split(d->av[d->child + 2 + d->heredoc], ' ');
		if (!d->cmd_options)
			error_bonus(error_msg_bonus("unexpected error", "", "", 1), d);
		d->cmd_path = get_cmd_bonus(d->cmd_options[0], d);
		d->pids[d->child] = fork();
		if (d->pids[d->child] == -1)
			error_bonus(error_msg_bonus("fork", ": ", strerror(errno), 1),
				d);
		else if (d->pids[d->child] == 0)
			execute_child_command(d);
		free_str_or_arr_bonus(d->cmd_path, d->cmd_options);
		d->child++;
	}
	exit_code = wait_for_children(d);
	if (d->heredoc == 1)
		unlink(".heredoc.tmp");
	return (exit_code);
}

int	pipex_main(int ac, char **av, char **envp)
{
	t_data	d;
	int		exit_code;

	if (ac < 5)
	{
		if (ac >= 2 && !ft_strncmp("here_doc", av[1], 9))
			return (error_msg_bonus("Usage: ",
					"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.",
					"", 1));
		return (error_msg_bonus("Usage: ",
				"./pipex file1 cmd1 cmd2 ... cmdn file2.", "", 1));
	}
	else if (ac < 6 && !ft_strncmp("here_doc", av[1], 9))
		return (error_msg_bonus("Usage: ",
				"./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2.", "", 1));
	if (!envp || envp[0][0] == '\0')
		error_bonus(error_msg_bonus("Unexpected error.", "", "", 1), &d);
	d = init_bonus(ac, av, envp);
	exit_code = execute_pipeline(&d);
	return (exit_code);
}
