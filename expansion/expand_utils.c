/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:41:13 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 14:09:52 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_quote_and_find(char *s, int *i, char quote)
{
	int	start;

	start = *i;
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (!s[*i])
		return (-1);
	return (0);
}

int	find_next_char(char *s, char target, int j)
{
	int	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			if (skip_quote_and_find(s, &i, s[i]) == -1)
				return (-1);
		}
		else if (s[i] == target && i > j)
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

char	*cmp_value_name(char *line, char *name, t_env_exp *env)
{
	int		i;
	char	*result;

	i = -1;
	while (++i < env->num_env)
	{
		if (exp_strcmp(name, env->env[i]) == 0)
		{
			free(name);
			result = extract_env_value(env->env[i]);
			return (expand_line(line, result));
		}
		else if (i + 1 == env->num_env)
		{
			free(name);
			return (expand_line(line, ft_strdup("")));
		}
	}
	return (0);
}
