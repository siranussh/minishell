/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:06 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/04 21:50:53 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	built_in_exit(int argc, char **args, t_data *data)
{
	long	status;

	if (!args || !*args)
		return (-1);
	write(STDERR_FILENO, "exit\n", 5);
	if (argc == 1)
		exit(data->p->exit_code);
	if (!is_number(args[1]) || is_long_overflow(args[1]))
	{
		print_error("minishell: exit", args[1], "numeric argument required");
		exit(2);
	}
	if (argc > 2)
	{
		print_error("minishell", "exit", "too many arguments");
		return (1);
	}
	status = ft_atol(args[1]);
	exit(status % 256);
}
