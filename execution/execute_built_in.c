/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:04:00 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:44:56 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	only_builtin(t_cmd *cmd, t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;
	int	exit_code;

	if (!is_built_in(cmd->tokens) || ft_cmd_size(cmd) != 1)
		return (-1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	parse_redirs(cmd);
	// process_all_heredocs(cmd);
	setup_redirs(cmd);
	exit_code = run_built_in(args_count(cmd->tokens),
			cmd->tokens, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	set_status(exit_code);
	return (exit_code);
}
