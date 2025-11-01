/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:28:16 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/01 17:07:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_closing_quote(int i, char *str, char c)
{
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	check_quotes_type(char *s)
{
	int	i;
	int	single;
	int	is_double;

	i = -1;
	single = 1;
	is_double = 1;
	while (s[++i])
	{
		if (s[i] == '"')
			is_double *= -1;
		if (s[i] == '\'')
			single *= -1;
		if (s[i] == ' ' && s[i + 1] == 34 && s[i + 2] == 34 && s[i + 3] == ' ')
			return (-1);
		else if (s[i] == ' ' && s[i + 1] == 39 && s[i + 2] == 39 && s[i
				+ 3] == ' ')
			return (-1);
		else if ((s[i] == 34 && s[i + 1] == 34 && single != -1) || (s[i] == 39
				&& s[i + 1] == 39 && is_double != -1))
			return (-1);
	}
	return (0);
}

static int	check_quote_has_pair(char *str, int *i, char c)
{
	int	quote_count;

	quote_count = 1;
	while (str[*i + 1] && str[*i + 1] != c)
		(*i)++;
	if (str[*i + 1] == c)
		quote_count++;
	(*i)++;
	return (quote_count);
}

int	check_dquote(char *str, int is_double, int is_single, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
			is_double += check_quote_has_pair(str, &i, str[i]);
		if (str[i] == 39)
			is_single += check_quote_has_pair(str, &i, str[i]);
		if (is_double % 2 != 0 || is_single % 2 != 0)
		{
			data->flags->quote = 1;
			printf("dquote>\n");
			return (0);
		}
		i++;
	}
	return (1);
}
