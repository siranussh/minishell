/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/08 21:48:49 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*remove_empty_quotes(char *str, int i)
{
	char	*new_str;

	str[i] = 27;
	str[i + 1] = 27;
	new_str = ft_strdup(str);
	free(str);
	return (delete_quotes(new_str, 27));
}

static char	*remove_empty_quotes_arg(char *str, int i)
{
	int		j;
	char	*new_str;

	str[i] = 48;
	str[i + 1] = ';';
	j = -1;
	new_str = malloc(sizeof(char) * ft_strlen(str));
	if (!new_str)
		exit_error("minishell: malloc failed", 1);
	while (++j < i)
		new_str[j] = str[j];
	while (str[j + 1])
	{
		new_str[j] = str[j + 1];
		j++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*skip_empty_quotes(char *s, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] == 34 && s[i + 1] && s[i + 1] != 34)
			|| (s[i] == 39 && s[i + 1] && s[i + 1] != 39))
				i = find_closing_quote(i + 1, s, s[i]);
		if (s[i] == 32 && (s[i + 1] == 34 || s[i + 1] == 39) && (s[i + 2] == 34
				|| s[i + 2] == 39) && (s[i + 3] == 32 || !s[i + 3]))
		{
			i++;
			s = remove_empty_quotes_arg(s, i);
			s = skip_empty_quotes(s, cmd);
		}
		else if ((s[i] == 34 && s[i + 1]
				&& s[i + 1] == 34) || (s[i] == 39 && s[i + 1] == 39))
		{
			s = remove_empty_quotes(s, i);
			cmd->num_tokens--;
			return (skip_empty_quotes(s, cmd));
		}
	}
	return (s);
}

char	*delete_quotes(char *str, char c)
{
	int		i;
	int		len;
	char	*temp;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (str[i] != c)
		len++;
	}
	temp = malloc(sizeof(char) * len + 1);
	if (!temp)
		exit_error("minishell: malloc failed", 1);
	while (--i >= 0)
	{
		if (str[i] != c)
		{
			temp[len] = str[i];
			len--;
		}
	}
	free(str);
	return (temp);
}
