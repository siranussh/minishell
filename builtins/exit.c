/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:06 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 12:48:23 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (data)
			free_data(data);
		exit(last_status);
	}
	if (!is_number(args[1]) || is_long_overflow(args[1]))
	{
		print_error("minishell: exit", args[1], "numeric argument required");
		if (data)
			free_data(data);
		exit(2);
	}
	if (argc > 2)
	{
		print_error("minishell", "exit", "too many arguments");
		return (1);
	}
	status = ft_atol(args[1]);
	if (data)
		free_data(data);
	exit(status % 256);
}
