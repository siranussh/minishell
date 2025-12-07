/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:06 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:12:42 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exit_with_code(t_data *data, int status)
{
	if (data)
		free_data(data);
	exit(status);
}

int	built_in_exit(int argc, char **args, t_data *data)
{
	long	status;
	int		last_status;

	if (!args || !*args)
		return (-1);
	write(STDERR_FILENO, "exit\n", 5);
	if (argc == 1)
	{
		last_status = data->exit_code;
		exit_with_code(data, last_status);
	}
	if (!is_number(args[1]) || is_long_overflow(args[1]))
	{
		print_error("minishell: exit", args[1], "numeric argument required");
		exit_with_code(data, 2);
	}
	if (argc > 2)
		return (print_error("minishell", "exit", "too many arguments"), 1);
	status = ft_atol(args[1]);
	if (data)
		free_data(data);
	exit(status % 256);
}
