/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:00:07 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/24 14:24:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	which_redir(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return (0);
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			return (1);
		else if (ft_strcmp(args[i], "<") == 0)
			return (2);
		else if (ft_strcmp(args[i], ">") == 0)
			return (3);
		else if (ft_strcmp(args[i], ">>") == 0)
			return (4);
		i++;
	}
	return (0);
}

char	*return_infile_redir(char **args, char *redir)
{
	int	i;

	if (!args || !*args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], redir == 0))
			return (i++, args[i]);
		i++;
	}
	return (NULL);
}

char	*return_infile(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<") == 0)
			return (i++, args[i]);
		i++;
	}
	return (NULL);
}
