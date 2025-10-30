/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:42:43 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/30 16:32:05 by sihakoby         ###   ########.fr       */
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

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			i = find_closing_quote(i + 1, str, str[i]);
			if (i == -1)
				return (-1);
		}
			
		if (str[i] == '>' && !is_other_op(str[i + 1]))
			return (1);
		if (str[i] == '>' && str[i + 1] == '>' && !is_other_op(str[i + 2]))
			return (2);
		if (str[i] == '<' && !is_other_op(str[i + 1]))
			return (3);
		if (str[i] == '<' && str[i + 1] == '<' && !is_other_op(str[i + 2]))
			return (4);
		if (str[i] == '2' && str[i + 1] == '>' && !is_other_op(str[i + 2]))
			return (5);
		if (str[i] == '2' && str[i + 1] == '>' && str[i + 2] == '>')
			return (6);
		if (is_other_op(str[i]))
			return (-1);
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
	int i;
	i = 0;
	while (str[i] && !is_other_op(str[i]))
		i++;
	return (i);
}
