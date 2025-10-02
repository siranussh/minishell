/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 23:21:01 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/02 23:21:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

void	giving_new_value(t_env **env, char *key, char *value)
{
	char	*new_value;
	t_env	*head;

	head = *env;
	new_value = ft_strjoin(if_env_value_exist(*env, key), value);
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			free(head->value);
			head->value = new_value;
			break;
		}
		head = head->next;
	}
}

void	append_export(t_env **env, char *key, char *value)
{
	int		key_exists_before;
	int		had_value_before;

	if (get_env_key_index(*env, key) != -1)
		key_exists_before = 1;
	else
		key_exists_before = 0;
	if (if_env_value_exist(*env, key))
		had_value_before = 1;
	else
		had_value_before = 0;
	key_existance(env, key, value);
	if (key_exists_before && had_value_before)
		giving_new_value(env, key, value);
}
