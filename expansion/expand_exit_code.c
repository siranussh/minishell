/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:40:51 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 14:08:24 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_exit_code(char *str, int i)
{
	char	*before;
	char	*after;
	char	*err_str;
	char	*tmp;
	char	*result;

	err_str = ft_itoa(g_exit_code);
	if (!err_str)
		return (NULL);
	before = ft_substr(str, 0, i);
	after = ft_strdup(str + i + 2);
	if (!before || !after || !err_str)
		return (free(before), free(after), free(err_str), NULL);
	tmp = ft_strjoin(before, err_str);
	free(before);
	free(err_str);
	if (!tmp)
		return (free(after), NULL);
	result = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	free(str);
	return (result);
}

char	*replace_all_exit_code(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			str = replace_exit_code(str, i);
			i = 0;
			if (!str)
				return (NULL);
		}
		else
			i++;
	}
	return (str);
}

int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_');
}

int	get_var_len(char *s, int i)
{
	int	len;

	len = 0;
	while (s[i + len] && is_var_char(s[i + len]))
		len++;
	return (len);
}
