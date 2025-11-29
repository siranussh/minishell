/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_list_handler2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:32:55 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 12:32:59 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_env_list(t_env *env_list)
{
	int	count;

	count = 0;
	while (env_list)
	{
		count++;
		env_list = env_list->next;
	}
	return (count);
}

static char	**alloc_env_array(int count)
{
	char	**env;

	env = ft_calloc(count + 1, sizeof(char *));
	if (!env)
		exit_error("malloc failed", 1);
	return (env);
}

static void	fill_env_array(t_env *env_list, char **env_array)
{
	int	i;

	i = 0;
	while (env_list)
	{
		if (env_list->value)
			env_array[i] = ft_strjoin_three(env_list->key, "=",
					env_list->value);
		else
			env_array[i] = ft_strdup(env_list->key);
		if (!env_array[i])
			exit_error("malloc failed", 1);
		i++;
		env_list = env_list->next;
	}
	env_array[i] = NULL;
}

t_env_exp	*env_exp_from_list(t_env *env_list)
{
	t_env_exp	*exp;
	int			count;

	if (!env_list)
		return (NULL);
	count = count_env_list(env_list);
	exp = ft_calloc(1, sizeof(t_env_exp));
	if (!exp)
		exit_error("malloc failed", 1);
	exp->env = alloc_env_array(count);
	exp->num_env = count;
	exp->path = NULL;
	fill_env_array(env_list, exp->env);
	return (exp);
}
