/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_handler2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:06:43 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 14:06:55 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	has_only_dollars_or_dollars_before_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '$')
		i++;
	if (s[i] == '\0')
		return (1);
	if (ft_isalpha(s[i]) || s[i] == '_')
		return (1);
	return (0);
}

char	*make_prefix(int prefix_len)
{
	char	*prefix;
	int		i;

	prefix = ft_calloc(prefix_len + 1, 1);
	if (!prefix)
		return (NULL);
	i = 0;
	while (i < prefix_len)
	{
		prefix[i] = '$';
		i++;
	}
	return (prefix);
}

char	*build_insert(char *line, int pos, int dollar_count, int var_len,
		t_env_exp *env)
{
	char	*prefix;
	char	*var;
	char	*val;
	char	*insert;

	prefix = make_prefix(dollar_count - 1);
	var = ft_substr(line, pos + dollar_count, var_len);
	val = get_env_var(env, var, 0, &var_len);
	free(var);
	insert = exp_strjoin(prefix, val, 0, 0);
	free(prefix);
	free(val);
	return (insert);
}

char	*build_new_line(char *line, char *insert, int pos, int remove_len)
{
	char	*new_line;
	int		new_len;
	int		j;
	int		k;
	int		rest;

	new_len = ft_strlen(line) - remove_len + ft_strlen(insert) + 1;
	new_line = malloc(new_len);
	if (!new_line)
		return (NULL);
	j = 0;
	k = 0;
	while (k < pos)
		new_line[j++] = line[k++];
	k = 0;
	while (insert[k])
		new_line[j++] = insert[k++];
	rest = pos + remove_len;
	while (line[rest])
		new_line[j++] = line[rest++];
	new_line[j] = '\0';
	return (new_line);
}

char	*expand_var_with_prefix(char *line, int pos, int dollar_count,
		int var_len, t_env_exp *env)
{
	char	*insert;
	char	*new_line;
	int		remove_len;

	insert = build_insert(line, pos, dollar_count, var_len, env);
	if (!insert)
		return (NULL);
	remove_len = dollar_count + var_len;
	new_line = build_new_line(line, insert, pos, remove_len);
	free(insert);
	free(line);
	return (new_line);
}
