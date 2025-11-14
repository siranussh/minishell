/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_input_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:31:12 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/14 22:13:36 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	has_input_redir(t_redir *redir)
{
	if (redir->type == 1 || redir->type == 2)
		return (1);
	return (0);
}

void	setup_input(t_cmd *curr, int prev_fd)
{
	// if ((curr->fd_in > 0) || (curr->infile != NULL) || (curr->redirs && has_input_redir(curr->redirs)) )
	// 	return ;
	if (curr->heredoc && curr->fd_in != -1)
	{
		dup2(curr->fd_in, STDIN_FILENO);
		close(curr->fd_in);
	}
	else if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
}

void	setup_output(t_cmd *curr, int pipe_fd[])
{
	if (curr->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
}
