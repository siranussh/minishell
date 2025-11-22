/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:35 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 23:50:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	update_env_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = value;
		}
		tmp = tmp->next;
	}
}

void	key_existance(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	if (get_env_key_index(*env, key) == -1)
	{
		tmp = ft_env_new(key, value);
		ft_env_add_back(env, tmp);
	}
	else if (get_env_key_index(*env, key) != -1)
		update_env_value(env, key, value);
}

void	handle_export_arg(t_env **env, char *arg)
{
	int		key_size;
	char	*key;
	char	*value;

	key_size = return_key_size_export(arg);
	key = return_key_export(arg);
	if (ft_strcmp(key, "_") == 0)
		return ;
	value = return_value_export(arg);
	if (arg[key_size] == '+')
		append_export(env, key, value);
	else
		key_existance(env, key, value);
}

int	is_valid_identifier(char *arg)
{
	int	i;

	if (!ft_isalpha(*arg) && *arg != '_')
		export_error(arg);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			
			if (arg[i] == '+' && arg[i + 1] == '=')
				i++;
			else
			{
				export_error(arg);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	print_export(char **env_arr, t_env **env)
{
	int		i;
	char	*env_value;

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
