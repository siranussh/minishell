/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:45:22 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/29 14:45:24 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_key_size(char *arg)
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

char	*return_key(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_key_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr_ms(arg, 0, index));
}

char	*return_value(char *arg)
{
	int	index;

	if (!arg || !*arg)
		return (NULL);
	index = return_key_size(arg);
	if (index < 0)
		return (NULL);
	return (ft_substr_ms(arg, index + 1, ft_strlen_ms(arg) - index - 1));
}

t_env	*env_parse(char **envp)
{
	char	*key;
	char	*value;
	t_env	*head;
	t_env	*tmp;

	head = NULL;
	while (*envp)
	{
		key = return_key(*envp);
		value = return_value(*envp);
		tmp = ft_env_new(key, value);
		ft_env_add_back(&head, tmp);
		free(key);
		free(value);
		envp++;
	}
	return (head);
}
