/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:48:12 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/23 18:26:18 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*if_env_key_exist(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	get_env_key_index(t_env *env, char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (-1);
	while (env)
	{
		// printf("env->name = %s, key = %s\n", env->name, key);
		if (ft_strcmp(env->name, key) == 0)
		{
			// printf("zibil qeez %s           i =====%d\n", key, i);
			return (i);
		}
		// else
		// {
		env = env->next;
		i++;
		// }
	}
	// printf("cankacac zibil((((((((((\n");
	// printf("*******env->name = %s, key = %s\n", env->name, key);
	return (-1);
}

void	del_env_node(t_env *prew)
{
	t_env	*tmp;

	if (!prew)
		return ;
	tmp = prew->next;
	free(tmp->name);
	free(tmp->value);
	prew->next = tmp->next;
	free(tmp);
}

int	built_in_unset(char **args, t_env *env)
{
	int		i;
	int		j;
	int		nb;
	int		prew_index;
	t_env	*prew;

	i = 1;
	j = 0;
	// prew = NULL;
	if (!args || !*args)
		return (0);
	while (args[i])
	{
		printf("stexa %s\n%d\n\n", args[i], nb);
		nb = get_env_key_index(env, args[i]);
		if (nb == -1)
		{
			printf("stex chpetq a mtnes %s\n\n\n", args[i]);
			// printf("index = %d\n", nb);
			i++;
		}
		else
		{
			prew_index = nb - 1;
			j = 0;
			while (env)
			{
				if (j == prew_index)
				{
					prew = env;
					del_env_node(prew);
					break ;
				}
				env = env->next;
				j++;
			}
			i++;
		}
		// printf("lerinik in red =%d\n", i);
	}
	return (1);
}
