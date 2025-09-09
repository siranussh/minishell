/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:24:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/09 15:11:23 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	return_name_size(char *arg)
{
	int	i;

	i = 0;
	if (!arg || !arg)
		return (-1);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	env_parse(char **envp)
{
	int		i;
	int		name_len;
	char	*name;
	char	*value;

	i = 0;
	/////////////////////////////////////////////////////////////////////////////
	while(envp[i])
	{
		name_len = return_name_size(envp[i]);
		name = (char *)malloc(name_len + 1);
		value = (char *)malloc(ft_strlen(envp[i]) - name_len);
		i++;
	}
	/////////////////////////////////////////////////////////////////////////////
}
