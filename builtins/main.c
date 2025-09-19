/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 13:18:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/17 16:00:23 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// char *str[] = {"echo", "-n", "-nn", "barev", "aziz", "-nnnnn", "-n", "jan", NULL};
	// built_in_env(envp);
	t_env	*env;

	env = env_parse(envp);
	// while (env)
	// {
	// 	printf("%s=%s\n", env->name, env->value);
	// 	env = env->next;
	// }
	built_in_env(env);

	return (0);
}
