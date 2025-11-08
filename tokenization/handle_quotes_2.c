/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/08 18:31:39 by anavagya         ###   ########.fr       */
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
	int		k;
	char	*new_str;

	str[i] = 27;
	str[i + 1] = 27;
	j = 0;
	k = 0;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str)
		exit_error("minishell: malloc failed", 1);
	while (str[j])
	{
		if (str[j] != 27)
		{
			new_str[k] = str[j];
			k++;
		}
		j++;
	}
	new_str[k] = '\0';
	free(str);
	return (new_str);
}

char	*skip_empty_quotes(char *s, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && s[i + 1] == s[i])
		{
			s = remove_empty_quotes(s, i);
			cmd->num_tokens--;
			i = 0;
			continue ;
		}
		else if (s[i] == ' ' && ((s[i + 1] == '"' && s[i + 2] == '"')
				|| (s[i + 1] == '\'' && s[i + 2] == '\'')) && (s[i + 3] == ' '
				|| s[i + 3] == '\0'))
		{
			s = remove_empty_quotes_arg(s, i + 1);
			i = 0;
			continue ;
		}
		else if ((s[i] == '"' || s[i] == '\'') && s[i + 1] && s[i + 1] != s[i])
			i = find_closing_quote(i + 1, s, s[i]);
		i++;
	}
	return (s);
}

char	*delete_quotes(char *str, char c)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = 0;
	len = 0;
	while (str[len])
		if (str[len++] != c)
			return (NULL);
	temp = malloc(sizeof(char) * (len - (len - j) + 1));
	if (!temp)
		exit_error("minishell: malloc failed", 1);
	while (str[i])
	{
		if (str[i] != c)
			temp[j++] = str[i];
		i++;
	}
	temp[j] = '\0';
	free(str);
	return (temp);
}
