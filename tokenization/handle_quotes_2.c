/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 18:13:19 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_empty_quotes_skippable(char *str, int i)
{
	char	prev;
	char	next;
	int		prev_is_sep;
	int		next_is_sep;

	if (i == 0)
		prev = ' ';
	else
		prev = str[i - 1];
	if (str[i + 2] == '\0')
		next = ' ';
	else
		next = str[i + 2];
	prev_is_sep = (prev == ' ' || prev == '\t' || prev == '\n'
			|| prev == '|' || prev == '<' || prev == '>');
	next_is_sep = (next == ' ' || next == '\t' || next == '\n'
			|| next == '|' || next == '<' || next == '>');
	return (prev_is_sep && next_is_sep);
}

char	*skip_empty_quotes(char *str, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;

	(void)cmd;
	if (!str)
		return (NULL);
	res = malloc(strlen(str) + 1);
	if (!res)
		exit_error("malloc failed", 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"') || (str[i] == '\''
				&& str[i + 1] == '\''))
			i = handle_quote_pair(str, res, i, &j);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
