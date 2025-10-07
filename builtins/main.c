/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:37:55 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/07 22:27:41 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	// t_env	*env;

	(void)argc;
	(void)argv;
	(void)envp;
	// char *str_echo[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	// char *str_env[] = {"env", NULL};
	// char *str[] = {"export", "zibil=foo", "ANfgh+=asd", NULL};
	// char *str1[] = {"export", "zibil=bar", NULL};
	// char *str_unset[] = {"unset", "_", NULL};
	char *str_exit[] = {"exit", "42", NULL};
	
	built_in_exit(2, str_exit);
	// built_in_echo(str_echo);
	// env = env_parse(envp);
	// built_in_env(1, str_env, env);
	// printf("\n--------------------------------------------------------\n");

	// built_in_export(str, 3, &env);
	// printf("\n--------------------------------------------------------\n");
	// built_in_env(1, str_env, env);
	// printf("\n\n\n");
	// built_in_export(str, 1, &env);
	// printf("\n\n\n");

	// built_in_export(str1, 2, &env);
	// built_in_export(str, 1, &env);
	// printf("\n\n\n");
	// built_in_unset(str_unset, &env);
	// built_in_env(1, str_env, env);
	return (0);
}
