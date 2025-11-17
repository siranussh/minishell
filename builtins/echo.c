/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:33 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/17 23:00:37 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

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
		return (write(STDOUT_FILENO, "\n", 1), 0);
	index++;
	while (args[index])
	{
		write(STDOUT_FILENO, args[index], strlen(args[index]));
		if (args[index + 1])
			write(STDOUT_FILENO, " ", 1);
		index++;
	}
	if (n_flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
