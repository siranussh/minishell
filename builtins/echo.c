/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:54:20 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/07 22:10:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || !*str || str[0] != '-')
		return (0);
	i = 0;
	if (str[i] == '-' && !str[i + 1])
		return (0);
	else if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_n_flag(char **args)
{
	int	i;

	if (!args || !*args || !args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (is_n_flag(args[i]) == 0 && i == 1)
			return (0);
		else if (is_n_flag(args[i]))
			i++;
		else
			break ;
	}
	return (--i);
}

int	built_in_echo(char **args)
{
	int	index;
	int	n_flag;

	index = 0;
	if (!args || !*args)
		return (0);
	n_flag = check_n_flag(args);
	index = n_flag;
	if (!args[index])
		return (printf("\n"), 0);
	index++;
	while (args[index])
	{
		printf("%s", args[index]);
		if (args[index + 1])
			printf(" ");
		index++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}
