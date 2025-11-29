/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:58:23 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/29 13:00:08 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_non_c(char *str, char c)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			len++;
		i++;
	}
	return (len);
}

char	*delete_quotes(char *str, char c)
{
	int		len;
	int		i;
	int		j;
	char	*temp;

	len = count_non_c(str, c);
	temp = malloc(len + 1);
	if (!temp)
		exit_error("malloc failed", 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	free(str);
	return (temp);
}
