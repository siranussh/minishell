/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:40:51 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/30 16:31:28 by sihakoby         ###   ########.fr       */
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
	if (!before || !after)
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
	int	j;

	i = find_closing_quote(0, str, '?') - 1;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			str = replace_exit_code(str, i);
		j = i;
		i = find_closing_quote(0, str, '$');
		if (j == i)
			break ;
	}
	return (str);
}
