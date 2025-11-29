/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:05:23 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 15:56:48 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*collapse_dollars(char *s)
{
	int	i;

	i = 0;
	while (s[i] == '$')
		i++;
	if (s[i] == '\0')
		return (ft_strdup("$"));
	return (ft_strdup("$"));
}

char	*get_env_var(t_env_exp *env, char *s, int i, int *len)
{
	char	*name;
	char	*val;
	int		j;

	*len = get_var_len(s, i);
	j = 0;
	name = ft_substr(s, i, *len);
	val = NULL;
	while (j < env->num_env)
	{
		if (ft_strncmp(env->env[j], name, ft_strlen(name)) == 0
			&& env->env[j][ft_strlen(name)] == '=')
		{
			val = extract_env_value(env->env[j]);
			break ;
		}
		j++;
	}
	free(name);
	if (!val)
		val = ft_strdup("");
	return (val);
}

// char	*expand_only_dollars(char *line, int pos, int dollar_count)
// {
// 	char	*new_line;
// 	int		j;
// 	int		k;
// 	int		i;
// 	int		rest;

// 	new_line = malloc(ft_strlen(line) - dollar_count + 2);
// 	if (!new_line)
// 		return (NULL);
// 	j = 0;
// 	k = 0;
// 	while (k < pos)
// 	{
// 		new_line[j++] = line[k];
// 		k++;
// 	}
// 	i = 0;
// 	while (i < dollar_count)
// 	{
// 		new_line[j++] = '$';
// 		i++;
// 	}
// 	rest = pos + dollar_count;
// 	while (line[rest])
// 		new_line[j++] = line[rest++];
// 	new_line[j] = '\0';
// 	free(line);
// 	return (new_line);
// }

char	*expand_only_dollars(char *line, int pos, int dollar_count)
{
	char	*new_line;
	int		j;
	int		i;

	new_line = malloc(ft_strlen(line) - dollar_count + 2);
	if (!new_line)
		return (NULL);
	j = 0;
	i = 0;
	while (i < pos)
		new_line[j++] = line[i++];
	i = 0;
	while (i < dollar_count)
	{
		new_line[j++] = '$';
		i++;
	}
	i = pos + dollar_count;
	while (line[i])
		new_line[j++] = line[i++];
	new_line[j] = '\0';
	free(line);
	return (new_line);
}

static char	*get_env_val(char *line, int pos, t_env_exp *env, int *remove_len)
{
	int		dollar_count;
	int		var_len;
	char	*var;
	char	*val;

	dollar_count = count_dollars(line, pos);
	var_len = get_var_len(line, pos + dollar_count);
	if (var_len == 0)
	{
		*remove_len = dollar_count;
		return (NULL);
	}
	var = ft_substr(line, pos + dollar_count, var_len);
	val = get_env_var(env, var, 0, &var_len);
	free(var);
	*remove_len = dollar_count + var_len;
	return (val);
}

char	*expand_dollars_simple(char *line, int pos, t_env_exp *env)
{
	char	*val;
	char	*new_line;
	int		remove_len;

	val = get_env_val(line, pos, env, &remove_len);
	if (!val)
		return (expand_only_dollars(line, pos, remove_len));
	new_line = build_new_line(line, val, pos, remove_len);
	free(val);
	free(line);
	return (new_line);
}
// char	*expand_dollars_simple(char *line, int pos, t_env_exp *env)
// {
// 	int		dollar_count;
// 	int		start_var;
// 	int		var_len;
// 	int		remove_len;
// 	char	*var;
// 	char	*val;
// 	char	*new_line;

// 	dollar_count = count_dollars(line, pos);
// 	start_var = pos + dollar_count;
// 	var_len = get_var_len(line, start_var);
// 	if (var_len == 0)
// 		return (expand_only_dollars(line, pos, dollar_count));
// 	var = ft_substr(line, start_var, var_len);
// 	val = get_env_var(env, var, 0, &var_len);
// 	free(var);
// 	remove_len = dollar_count + var_len;
// 	new_line = build_new_line(line, val, pos, remove_len);
// 	free(val);
// 	free(line);
// 	return (new_line);
// }
