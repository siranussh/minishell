/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:05 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/30 14:13:54 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': ", 2);
	}
	ft_putstr_fd("not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
