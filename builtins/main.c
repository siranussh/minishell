/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:37:55 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/04 22:05:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	char *str_env[] = {"env", NULL};
	char *str[] = {"export", "zibil=foo", "ANfgh+=asd", NULL};
	char *str1[] = {"export", "zibil=bar", NULL};
	char *str_unset[] = {"unset", "_", NULL};
	env = env_parse(envp);
	built_in_env(1, str_env, env);
	printf("\n--------------------------------------------------------\n");

	built_in_export(str, 3, &env);
	printf("\n--------------------------------------------------------\n");
	built_in_env(1, str_env, env);
	printf("\n\n\n");
	built_in_export(str, 1, &env);
	printf("\n\n\n");

	built_in_export(str1, 2, &env);
	built_in_export(str, 1, &env);
	printf("\n\n\n");
	built_in_unset(str_unset, &env);
	built_in_env(1, str_env, env);
	return (0);
}
