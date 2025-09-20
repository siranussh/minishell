/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:50 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/17 17:52:39 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_path(t_env *env)
{
	while (env)
	{
		if (ft_strncmp(env->name, "PATH", 4) == 0)
			return (1);
		else
			env = env->next;

	}
	return (0);
}

int	built_in_env(t_env *env)
{
	if (check_path(env) == 0)
	{
		printf("%s\n", "minishell: env: No such file or directory");
		return (0);
	}
	while (env)
	{
		printf("%s", env->name);
		if (env->value)
			printf("=%s", env->value);
		printf("\n");
		env = env->next;
	}
	return (1);
}
