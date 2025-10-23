/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:41:52 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/23 08:00:24 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

char	*extract_env_value(char *str)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(""));
	len = ft_strlen(str) - (i + 1);
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		exit_error("minishell: malloc failed", 1);
	ft_strlcpy(value, str + i + 1, len + 1);
	return (value);
}

char	*expand_dollar(char *new_line, char *line, char *var, int c)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = find_next_char(line, '$', -1);
	if ((size_t)k == ft_strlen(line))
		return (line);
	while (++i < k)
		new_line[i] = line[i];
	while (var[++j])
		new_line[i + j] = var[j];
	while (line[i + c])
	{
		new_line[i + j] = line[i + c];
		i++;
	}
	new_line[i + j] = '\0';
	return (new_line);
}

char	*expand_line(char *line, char *var)
{
	int		i;
	int		j;
	char	*new_line;

	i = find_next_char(line, '$', -1);
	if (i < 0)
		return (ft_strdup(line));
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i
		+ j] != 39)
		j++;
	new_line = malloc(ft_strlen(line) - j + ft_strlen(var) + 1);
	if (!new_line)
		exit_error("minishell: malloc failed", 1);
	new_line = expand_dollar(new_line, line, var, j);
	free(line);
	free(var);
	return (new_line);
}

char	*delete_invalid_dollar(char *str, int i, int j)
{
	char	*new_str;

	while (str[++i])
	{
		if (str[i] && str[i] == '$' && str[i + 1] && is_digit_or_special(str[i
				+ 1]) == 1)
		{
			j = -1;
			new_str = malloc(sizeof(char) * ft_strlen(str) - 1);
			if (!new_str)
				exit_error("minishell: malloc failed", 1);
			while (++j < i)
				new_str[j] = str[j];
			i++;
			while (str[++i])
			{
				new_str[j] = str[i];
				j++;
			}
			new_str[j] = '\0';
			free(str);
			str = delete_invalid_dollar(new_str, -1, -1);
		}
	}
	return (str);
}

void	expand(t_cmd **cmd)
{
	int i;

	i = -1;
	if (check_dollar_purpose((*cmd)->cmd) == 1)
		(*cmd)->cmd = replace_all_val((*cmd), (*cmd)->cmd, NULL);
	if (is_tilde_path((*cmd)->cmd) == 1)
		(*cmd)->cmd = replace_tilde((*cmd)->cmd);
	if (!(*cmd)->tokens)
		return ;
	while ((*cmd)->tokens[++i])
	{
		if (check_dollar_purpose((*cmd)->tokens[i]) == 1)
			(*cmd)->tokens[i] = replace_all_val((*cmd), (*cmd)->tokens[i], NULL);
		if (is_tilde_path((*cmd)->tokens[i]) == 1)
			(*cmd)->tokens[i] = replace_tilde((*cmd)->tokens[i]);
	}
}