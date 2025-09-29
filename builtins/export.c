/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 12:23:25 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/29 23:03:09 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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

int	return_name_size_ex(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (ft_strlen(arg));
}

char	*return_name_ex(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_name_size_ex(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr(arg, 0, index));
}

char	*return_value_ex(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_name_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr(arg, index + 1, ft_strlen(arg) - index - 1));
}

int	built_in_export(char **args, int argc, t_env **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*env_value;
	char	**env_arr;
	t_env	*tmp;
	t_env	*head;

	if (!env)
		return (0);
	head = *env;
	i = 1;
	if (argc > 1)
	{
		while (args[i])
		{
			name = return_name_ex(args[i]);
			value = return_value_ex(args[i]);
			if (get_env_key_index(*env, name) == -1)
			{
				// printf("name = %s\n value = %s\n\n\n\n", name, value);
				tmp = ft_lstnew(name, value);
				ft_lstadd_back(env, tmp);
			}
			if (get_env_key_index(*env, name) != -1 && !if_env_value_exist(*env, name))
			{
				while (head)
				{
					if (ft_strcmp(head->name, name) == 0)
						head->value = value;
					head = head->next;
				}
			}
			i++;
		}
	}
	env_arr = convert_to_array(*env);
	sort_in_alpha_order(env_arr);
	if (argc == 1)
	{
		i = 0;
		while (env_arr[i])
		{
			env_value = if_env_value_exist(*env, env_arr[i]);
			if (env_value)
				printf("declare -x %s=\"%s\"\n", env_arr[i], env_value);
			else
				printf("declare -x %s\n", env_arr[i]);
			i++;
		}
	}
	ft_free(env_arr);
	return (1);
}
