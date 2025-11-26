/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:41:24 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/26 10:41:42 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_value_name(char *line)
{
	int		i;
	int		j;
	char	*name;

	i = find_closing_quote(0, line, '$') + 1;
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"' && line[i
		+ j] != 39 && is_special(line[i + j]) == 0)
		j++;
	name = ft_calloc(sizeof(char), j + 1);
	if (!name)
		exit_error("minishell: malloc failed", 1);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"' && line[i
		+ j] != 39 && is_special(line[i + j]) == 0)
	{
		name[j] = line[i + j];
		j++;
	}
	return (name);
}

char	*extract_after_special(char *line, int i, t_cmd *cmd)
{
	int		j;
	char	*rest;

	cmd->flags->has_special = 1;
	j = i;
	while (line[i])
		i++;
	rest = malloc(sizeof(char) * (i - j + 1));
	if (!rest)
		exit_error("minishell malloc failed", 1);
	i = 0;
	while (line[j])
	{
		rest[i] = line[j];
		i++;
		j++;
	}
	rest[i] = '\0';
	return (rest);
}

char	*replace_val(t_cmd *cmd, char *line, char **rest_line, t_env_exp *env)
{
	char	*name;
	int		i;

	if (ft_strnstr(line, "$?", ft_strlen(line)) != 0)
		return (replace_all_exit_code(line));
	name = extract_value_name(line);
	if (!name)
		return (NULL);
	if (!name[0])
		return (ft_strdup("$"));
	i = find_next_char(line, '$', -1);
	while (line[++i] && line[i] != ' ')
	{
		if ((is_special(line[i]) == -1 && line[i] != '$') || (line[i] == '$'
				&& i == find_next_char(line, '$', find_next_char(line, '$', -1)
					+ 1)))
		{
			*rest_line = extract_after_special(line, i, cmd);
			break ;
		}
	}
	return (cmp_value_name(line, name, env));
}

char	*replace_all_val(t_cmd *cmd, char *str, char *rest_line, t_env_exp *env)
{
	int		i;
	int		in_single;
	int		in_double;
	int		dollar_count;
	int		var_len;
	char	*var;
	char	*val;
	char	*new_str;

	i = 0;
	in_single = 0;
	in_double = 0;
	(void)cmd;
	(void)rest_line;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue ;
		}
		if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_single)
		{
			if (str[i + 1] && str[i + 1] == '?')
			{
				val = ft_itoa(g_exit_code);
				char *new_str = build_new_line(str, val, i, 2); // $?
				free(val);
				free(str);
				str = new_str;
				i += ft_strlen(new_str) - i;
				continue ;
			}
			dollar_count = 0;
			while (str[i + dollar_count] == '$')
				dollar_count++;
			var_len = get_var_len(str, i + dollar_count);
			if (var_len == 0)
			{
				i += dollar_count;
				continue ;
			}
			var = ft_substr(str, i + dollar_count, var_len);
			val = get_env_var(env, var, 0, &var_len);
			free(var);
			new_str = build_new_line(str, val, i, dollar_count + var_len);
			free(val);
			free(str);
			str = new_str;
			i += ft_strlen(val);
			continue ;
		}
		i++;
	}
	return (str);
}
