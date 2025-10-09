/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:28:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/09 19:28:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

char	**convert_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**env_arr;

	size = ft_env_size(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_arr[i] = ft_strdup(env->key);
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	sort_in_alpha_order(char **env_arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_arr[i])
	{
		j = i + 1;
		while (env_arr[j])
		{
			if (ft_strcmp(env_arr[i], env_arr[j]) > 0)
			{
				tmp = env_arr[i];
				env_arr[i] = env_arr[j];
				env_arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
