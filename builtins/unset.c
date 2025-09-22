/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:48:12 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/22 18:43:42 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*if_env_key_exist(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	del_env_value(t_env *prew)
{
	t_env	*tmp;

	if (!prew || !prew->next)
		return ;
	tmp = prew->next;
	free(tmp->name);
	free(tmp->value);
	prew->next = tmp->next;
	free(tmp);
}

int	built_in_unset(char **args);
{
	int	i;

	i = 1;
	if (!args || !*args)
		return (0);
	while (args[i])
	{
		if (!if_env_key_exist(env, args[i]))
			i++;
		else
		{
			ft_lstdelone(env, )
			i++;
		}
	}
}
