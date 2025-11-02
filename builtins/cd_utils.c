/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:46:36 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/02 18:48:18 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

char	*get_env_values(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) != 0)
			env = env->next;
		else
			return (env->value);
	}
	return (NULL);
}

int	change_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
