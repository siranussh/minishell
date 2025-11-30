/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/30 14:18:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

char	*if_env_value_exist(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	return_key_size_export(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=' || arg[i] == '+')
			return (i);
		i++;
	}
	return (ft_strlen_ms(arg));
}

char	*return_key_export(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_key_size_export(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr_ms(arg, 0, index));
}

char	*return_value_export(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_key_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr_ms(arg, index + 1, ft_strlen_ms(arg) - index - 1));
}

int	built_in_export(char **args, int argc, t_env **env)
{
	int		i;
	char	**env_arr;

	if (!env)
		return (1);
	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			if (is_valid_identifier(args[i]) == 1)
				handle_export_arg(env, args[i]);
			else
				return(export_error(args[i]));
			i++;
		}
	}
	env_arr = convert_to_array(*env);
	sort_in_alpha_order(env_arr);
	if (argc == 1)
		print_export(env_arr, env);
	ft_free(env_arr);
	return (0);
}
