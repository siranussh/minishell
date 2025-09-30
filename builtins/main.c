/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/30 16:28:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-n", "jan", NULL};
	char *str[] = {"export", "zibil=vaayyyyyyyy", "-+AAAAAA","AN=fehg", NULL};
	// char *str1[] = {"export", "zibil=vay", NULL};
	// char *str_unset[] = {"unset", "zibil", NULL};
	env = env_parse(envp);
	built_in_export(str, 4, &env);
	built_in_env(env);
	// built_in_unset(str, &env);
	printf("\n\n\n");
	built_in_export(str, 1, &env);
	printf("\n\n\n");

	return (0);
}
