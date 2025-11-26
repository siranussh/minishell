/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:15 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/26 22:30:00 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	built_in_exit(int argc, char **args)
{
	long	status;

	if (!args || !*args)
		return (-1);
	printf("exit\n");
	if (argc == 1)
		exit(g_exit_code);
	if (argc > 2)
	{
		print_error("minishell", "exit", "too many arguments");
		g_exit_code = 1;
		return (1);
	}
	if (!is_number(args[1]))
	{
		print_error("minishell: exit", args[1], "numeric argument required");
		exit(2);
	}
	status = ft_atol(args[1]);
	exit(status % 256);
}
