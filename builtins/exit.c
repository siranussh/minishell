/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:06 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/29 14:46:08 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_in_exit(int argc, char **args)
{
	long	status;

	if (!args || !*args)
		return (-1);
	printf("exit\n");
	if (argc == 1)
		exit(g_exit_code);
	if (!is_number(args[1]) || is_long_overflow(args[1]))
	{
		print_error("minishell: exit", args[1], "numeric argument required");
		exit(2);
	}
	if (argc > 2)
	{
		print_error("minishell", "exit", "too many arguments");
		g_exit_code = 1;
		return (1);
	}
	status = ft_atol(args[1]);
	exit(status % 256);
}
