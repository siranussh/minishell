/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:25 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/26 13:48:46 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	**convert_to_array(t_env *env)
{
	int		i;
	int		size;
	char	**env_arr;

	size = ft_lstsize(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		env_arr[i] = ft_strdup(env->name);
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
	j = 1;
	while (env_arr[i])
	{
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

int	built_in_export(t_env *env)
{
	char **env_arr;

	if (!env)
		return (0);
	env_arr = convert_to_array(env);
	sort_in_alpha_order(env_arr);
	// dasavorel aybenakan kargov env-n minchev tpely
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
