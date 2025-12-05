/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:42:43 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 18:03:40 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_other_op(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	redir_type(char *str)
{
	int	i;
	int	ret;

	i = 0;
	if (!str || str[i] != '\0')
		return (0);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i = find_closing_quote(i + 1, str, str[i]);
			if (i == -1)
				return (-1);
		}
		ret = check_redir_at(str, i);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (0);
}

int	is_redir(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (redir_type(token[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	redir_smb(int c)
{
	if (c == 1 || c == 2 || c == 5 || c == 6)
		return ('>');
	else if (c == 3 || c == 4)
		return ('<');
	return (0);
}

int	find_next_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_other_op(str[i]))
		i++;
	return (i);
}
