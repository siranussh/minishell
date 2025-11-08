/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_input_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:31:12 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/30 16:31:12 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	setup_input(t_cmd *curr, int prev_fd)
{
	if (curr->heredoc && curr->fd_in != -1)
	{
		dup2(curr->fd_in, STDIN_FILENO);
		close(curr->fd_in);
	}
	// else if (curr->infile)
	// {
	// 	curr->fd_in = open(curr->infile, O_RDONLY);
	// 	if (curr->fd_in == -1)
	// 		perror("open infile");
	// 	if (curr->fd_in != STDIN_FILENO)
	// 	{
	// 		dup2(curr->fd_in, STDIN_FILENO);
	// 		close(curr->fd_in);
	// 	}
	// }
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	setup_output(t_cmd *curr, int pipe_fd[])
{
	// if (curr->outfile)
	// {
	// 	if (curr->append == 2)
	// 		curr->fd_out = open(curr->outfile,
	// 				O_WRONLY | O_CREAT | O_APPEND, 0644);
	// 	else
	// 		curr->fd_out = open(curr->outfile,
	// 				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// 	if (curr->fd_out == -1)
	// 		perror("open outfile");
	// 	if (curr->fd_out != STDOUT_FILENO)
	// 	{
	// 		dup2(curr->fd_out, STDOUT_FILENO);
	// 		close(curr->fd_out);
	// 	}
	// }
	// else if (curr->next)
	if (curr->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
}
