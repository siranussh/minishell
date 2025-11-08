/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:41:13 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/08 22:22:00 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_quote_and_find(char *s, int *i, char c, int j)
{
	if (c == '"')
	{
		while (s[++(*i)] && s[*i] != '"')
			if (s[*i] == '$' && *i > j)
				return (*i);
	}
	else
	{
		(*i)++;
		*i = find_closing_quote(*i, s, 39);
		if (*i == -1)
			return (-1);
	}
	return (0);
}

int	find_next_char(char *s, char c, int j)
{
	int	i;
	int	r;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == 39)
		{
			r = skip_quote_and_find(s, &i, s[i], j);
			if (r)
				return (r);
		}
		else if (s[i] == c && i > j)
			return (i);
	}
	return (-1);
}

int	is_special(char c)
{
	const char	*specials = "=@#-+{}[]!~?%^*/$;";

	if (ft_strchr(specials, c))
		return (-1);
	return (0);
}

char	*cmp_value_name(t_cmd *cmd, char *line, char *name)
{
	int		i;
	char	*result;

	i = -1;
	while (++i < cmd->env->num_env)
	{
		if (exp_strcmp(name, cmd->env->env[i]))
		{
			free(name);
			result = extract_env_value(cmd->env->env[i]);
			return (expand_line(line, result));
		}
		else if (i + 1 == cmd->env->num_env)
		{
			free(name);
			return (expand_line(line, ft_strdup("")));
		}
	}
	return (0);
}
