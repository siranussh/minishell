/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/04 13:21:44 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main()
{
	// char *str[] = {"echo", "-nnnnnnnnnnnnnnnnnnnnnnnnn", "-n", "spasi", NULL};
	// char *str[] = {"echo", "-n", NULL};
	// char *str[] = {NULL};
	// char *str[] = {"echo", NULL};
	char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-nnnnn", "-n", "jan", NULL};

	built_in_echo(str);
	return (0);
}
