/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:35:09 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/02 23:09:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

void	key_existance(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*head;

	head = *env;
	if (get_env_key_index(*env, key) == -1)
	{
		tmp = ft_env_new(key, value);
		ft_env_add_back(env, tmp);
	}
	else if (get_env_key_index(*env, key) != -1 && !if_env_value_exist(*env, key))
	{
		while (head)
		{
			if (ft_strcmp(head->key, key) == 0)
			{
				free(head->value);
				head->value = value;
			}
			head = head->next;
		}
	}
}

void	print_export(char **env_arr, t_env **env)
{
	int	i;
	char *env_value;

	i = 0;
	while (env_arr[i])
	{
		if (ft_strcmp(env_arr[i], "_") != 0)
		{
			env_value = if_env_value_exist(*env, env_arr[i]);
			if (env_value)
				printf("declare -x %s=\"%s\"\n", env_arr[i], env_value);
			else
				printf("declare -x %s\n", env_arr[i]);
		}
		i++;
	}
}
