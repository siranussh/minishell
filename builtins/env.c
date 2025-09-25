/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:52:21 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/25 12:49:10 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	built_in_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (1);
}
