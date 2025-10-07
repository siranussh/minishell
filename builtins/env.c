/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:52:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/07 23:34:07 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

int	built_in_env(int argc, char **args, t_env *env)
{
	if (argc > 1)
	{
		printf("minishell: env: '%s': No such file or directory\n", args[1]);
		return (1);
	}
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
