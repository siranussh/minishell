/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/20 19:13:54 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-nnnnn", "-n", "jan", NULL};
	char *str[] = {"cd", NULL};
	t_env	*env;

	env = env_parse(envp);
	built_in_cd(1, str, env);
	// while (env)
	// {
	// 	printf("%s=%s\n", env->name, env->value);
	// 	env = env->next;
	// }
	printf("\n\n\n");
	built_in_env(env);

	return (0);
}
