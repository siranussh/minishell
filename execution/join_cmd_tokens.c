/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:57:04 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/28 14:17:40 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

char	**join_cmd_tokens(t_cmd1 *cmd1)
{
	int		i;
	char	**args;

	args = (char **)malloc(sizeof(char *) * (cmd1->num_tokens + 2));
	if (!args)
		return (NULL);
	args[0] = ft_strdup(cmd1->cmd);
	i = 0;
	while (i < cmd1->num_tokens)
	{
		args[i + 1] = ft_strdup(cmd1->tokens[i]);
		i++;
	}
	args[i + 1] = NULL;
	return (args);
}
