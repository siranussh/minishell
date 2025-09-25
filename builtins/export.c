/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:25 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/25 17:23:09 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	sort_in_alpha_order(t_env **env)
{
	t_env	*tmp;
	t_env	*curr;

	tmp = *env;
	curr = *env;
	while (tmp->next)
	{
		while (curr)
		{
			if (ft_strcmp(tmp->name, curr->next->name) > 0)
				ft_lstswap(curr);
			curr = curr->next;
		}
		tmp = tmp->next;
	}
}

int	built_in_export(t_env *env)
{
	if (!env)
		return (0);
	// dasavorel aybenakan kargov env-n minchev tpely
	// sort_in_alpha_order(env);
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		else
			printf("declare -x %s\n", env->name);
		env = env->next;
	}
	return (1);

}
