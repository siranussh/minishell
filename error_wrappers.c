/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:43:05 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 22:07:09 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	pipe_syntax_error(t_data *data)
{
	print_error("minishell", NULL, "syntax error near unexpected token '|'");
	data->exit_code = 2;
	return (-1);
}

int	quote_error(t_data *data)
{
	print_error("minishell", NULL, "unexpected quote");
	data->exit_code = 2;
	return (-1);
}

int	redir_error(void)
{
	print_error("minishell", NULL, "syntax error near unexpected token '>'");
	return (-1);
}

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd("': ", STDERR_FILENO);
	}
	ft_putstr_fd("not a valid identifier", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	shlvl_error(char *arg)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("shell level (", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
	return (1);
}
