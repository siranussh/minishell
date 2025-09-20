/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:24:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/19 10:51:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	return_name_size(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !*arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*return_name(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_name_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr(arg, 0, index));
}

char	*return_value(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_name_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr(arg, index + 1, ft_strlen(arg) - index - 1));
}

t_env	*env_parse(char **envp)
{
	char	*name;
	char	*value;
	t_env	*head;
	t_env	*tmp;

	head = NULL;
	while (*envp)
	{
		name = return_name(*envp);
		value = return_value(*envp);
		tmp = ft_lstnew(name, value);
		ft_lstadd_back(&head, tmp);
		envp++;
	}
	return (head);
}
