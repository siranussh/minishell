/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/23 23:24:12 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	char *str[] = {"unset", "PWD", "SHELLLLL", NULL};
	env = env_parse(envp);
	built_in_env(env);
	built_in_unset(str, &env);
	printf("\n\n\n");
	built_in_env(env);
	return (0);
}
