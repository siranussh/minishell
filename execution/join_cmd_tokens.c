/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:57:04 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/30 17:46:03 by sihakoby         ###   ########.fr       */
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
