/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:27:57 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/09 19:27:58 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "builtins.h"

t_env	*ft_env_new(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
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

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}
