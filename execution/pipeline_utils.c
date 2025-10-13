/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:22:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 17:27:37 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	is_heredoc_redir_present(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		else if (str[i] == '<' && str[i + 1] != '<')
			return (2);
		else if (str[i] == '>' && str[i + 1] != '>')
			return (3);
		else if (str[i] == '>' && str[i + 1] == '>')
			return (4);
		i++;
	}
	return (0);
}

char	**cpy_str_arr(char **str)
{
	int		i;
	int		size;
	char	**str_cpy;

	if (!str || !*str)
		return (NULL);
	i = 0;
	size = args_count(str);
	str_cpy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str_cpy)
		return (NULL);
	while (str[i])
	{
		str_cpy[i] = ft_strdup(str[i]);
		i++;
	}
	str_cpy[i] = NULL;
	return (str_cpy);
}
