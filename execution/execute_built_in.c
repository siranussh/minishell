/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:58:56 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:58:56 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (setup_redirs(cmd) == -1)
		return (1);
	exit_code = run_built_in(args_count(cmd->tokens),
			cmd->tokens, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (exit_code);
}
