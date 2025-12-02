/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:57:04 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/02 12:45:00 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_cmd_tokens(char *cmd, char **tokens, int num_tokens)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (num_tokens + 2));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd);
	i = 0;
	while (i < num_tokens)
	{
		args[i + 1] = ft_strdup(tokens[i]);
		i++;
	}
	args[i + 1] = NULL;
	return (args);
}
