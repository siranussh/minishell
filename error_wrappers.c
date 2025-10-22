/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:05 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/22 16:21:51 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

int	pipe_syntax_error(t_data *data)
{
	print_error("minishell", NULL, "syntax error near unexpected token '|'");
	data->exit_status = 258;
	return (-1);
}

int	quote_error(t_data *data)
{
	print_error("minishell", NULL, "unexpected quote");
	data->exit_status = 258;
	return (-1);
}

int	redir_error(void)
{
	print_error("minishell", NULL, "syntax error near unexpected token '>'");
	return (-1);
}