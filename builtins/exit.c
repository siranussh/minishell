/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:15 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/27 17:20:45 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return (1);
	}
	if (!is_number(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	status = ft_atol(args[1]);
	exit(status % 256);
}
