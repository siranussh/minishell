/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/02 23:08:07 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	char *str[] = {"export", "zibil=barev", "AN+=vayy", NULL};
	char *str1[] = {"export", "_AN", NULL};
	// char *str_unset[] = {"unset", "zibil", NULL};
	env = env_parse(envp);
	built_in_export(str, 3, &env);
	built_in_env(env);
	printf("\n\n\n");
	built_in_export(str, 1, &env);
	built_in_export(str1, 2, &env);
	// built_in_unset(str, &env);
	built_in_export(str, 1, &env);
	printf("\n\n\n");
	built_in_env(env);

	return (0);
}
