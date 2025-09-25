/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:17:23 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/25 18:00:36 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_lstnew(char *name, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
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

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	ft_lstswap(t_env *env)
{
	t_env	*tmp;

	if (!env || !env->next)
		return ;
	tmp = env;
	env = env->next;
	tmp->next = env->next;
	env->next = tmp;
}
