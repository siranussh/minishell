/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:41:24 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 18:02:11 by sihakoby         ###   ########.fr       */
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
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && is_special(line[i + j]) == 0)
		j++;
	name = ft_calloc(sizeof(char), j + 1);
	if (!name)
		exit_error("minishell: malloc failed", 1);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && is_special(line[i + j]) == 0)
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

char	*replace_all_val(char *str, t_data *data)
{
	int		i;
	int		in_single;
	int		in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (handle_quotes(str[i], &in_single, &in_double))
		{
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_single)
		{
			str = handle_dollar(str, &i, data->env_exp, data);
			continue ;
		}
		i++;
	}
	return (str);
}
