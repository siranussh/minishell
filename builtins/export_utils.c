/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 13:35:09 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/02 18:32:38 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
