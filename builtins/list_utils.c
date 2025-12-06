/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:46:32 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/06 22:40:16 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

void	ft_env_add_back(t_env **lst, t_env *new)
{
	t_env	*current;

	current = *lst;
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

int	ft_env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env != NULL)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	del_env_node(t_env *prew)
{
	t_env	*tmp;

	if (!prew)
		return ;
	tmp = prew->next;
	free(tmp->key);
	free(tmp->value);
	prew->next = tmp->next;
	free(tmp);
}
