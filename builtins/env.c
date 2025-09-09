/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:50 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/09 14:25:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	built_in_env(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (0);
	i = 0;
	while (envp[i])
	{
		// stugel PATH ka te voch;
		printf("%s\n", envp[i]);
		i++;
	}
	return (1);
}
