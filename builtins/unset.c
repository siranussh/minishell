/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:24:03 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/30 16:29:36 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_key_index(t_env *env, char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (-1);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (-1);
}

static void	unset_head(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	*env = (*env)->next;
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

static void	unset_middle(t_env *head, int nb)
{
	int		j;
	t_env	*prew;

	prew = head;
	j = 0;
	while (prew && j < nb - 1)
	{
		prew = prew->next;
		j++;
	}
	if (prew)
		del_env_node(prew);
}

int	built_in_unset(char **args, t_env **env)
{
	int		i;
	int		nb;
	t_env	*head;

	i = 1;
	if (!args || !*args)
		return (0);
	while (args[i])
	{
		head = *env;
		if (ft_strcmp(args[i], "_") != 0)
		{
			nb = get_env_key_index(head, args[i]);
			if (nb == 0)
				unset_head(env);
			else if (nb > 0)
				unset_middle(head, nb);
		}
		i++;
	}
	return (0);
}
