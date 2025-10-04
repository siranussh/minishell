/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:38:54 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/04 23:49:44 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	built_in_exit(int argc, char **args)
{
	int	last_status;

	// last_status = 
	printf("exit\n");
	if (argc == 1)
		exit(last_status);
	if (argc > 2)
	{

		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!is_number(args[1]))
	{

		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	exit(ft_atol(args[1]) % 256);
}
