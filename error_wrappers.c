/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:05 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/01 12:48:45 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_syntax_error(void)
{
	print_error("minishell", NULL, "syntax error near unexpected token '|'");
	g_exit_code = 258;
	return (-1);
}

int	quote_error(void)
{
	print_error("minishell", NULL, "unexpected quote");
	g_exit_code = 258;
	return (-1);
}

int	redir_error(void)
{
	print_error("minishell", NULL, "syntax error near unexpected token '>'");
	return (-1);
}
