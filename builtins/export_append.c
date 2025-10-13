/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:22 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 11:23:22 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	giving_new_value(t_env **env, char *key, char *value)
{
	char	*new_value;

	new_value = ft_strjoin(if_env_value_exist(*env, key), value);
	update_env_value(env, key, new_value);
}

void	append_export(t_env **env, char *key, char *value)
{
	int		key_exists_before;
	int		had_value_before;
	t_env	*tmp;

	if (get_env_key_index(*env, key) != -1)
		key_exists_before = 1;
	else
		key_exists_before = 0;
	if (if_env_value_exist(*env, key))
		had_value_before = 1;
	else
		had_value_before = 0;
	if (get_env_key_index(*env, key) == -1)
	{
		tmp = ft_env_new(key, value);
		ft_env_add_back(env, tmp);
	}
	else if (get_env_key_index(*env, key) != -1
		&& !if_env_value_exist(*env, key))
		update_env_value(env, key, value);
	else if (key_exists_before && had_value_before)
		giving_new_value(env, key, value);
}
