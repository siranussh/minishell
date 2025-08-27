/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:09:32 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/27 18:36:44 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	built_in_echo(char **args)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (args[count])
	count++;
	if (i == 1)
		return (1);
	else
	{
		while (i < count)
		{
			write(1, &args[i], ft_strlen(args[i]));
			i++;
		}
	}
}
