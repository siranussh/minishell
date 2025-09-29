/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:25 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/29 18:35:05 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**convert_to_array(t_env *env)
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

static void	sort_in_alpha_order(char **env_arr)
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

char	*if_env_value_exist(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	built_in_export(char **args, int argc, t_env **env)
{
	int		i;
	char	*value;
	char	**env_arr;

	if (!env)
		return (0);
	i = 0;
	env_arr = convert_to_array(env);
	sort_in_alpha_order(env_arr);
	if (argc == 1)
	{
		while (env_arr[i])
		{
			value = if_env_value_exist(env, env_arr[i]);
			if (value)
				printf("declare -x %s=\"%s\"\n", env_arr[i], value);
			else
				printf("declare -x %s\n", env_arr[i]);
			i++;
		}
	}
	else
	{}
	ft_free(env_arr);
	return (1);
}
