/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/26 20:46:14 by sihakoby         ###   ########.fr       */
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

char *skip_empty_quotes(char *s, t_cmd *cmd)
{
    int i;

    if (!s)
        return (s);

    i = 0;
    while (s[i])
    {
        if (s[i] == '"' || s[i] == '\'')
        {
            if (s[i + 1] && s[i + 1] != s[i])
            {
                int new_i = find_closing_quote(i + 1, s, s[i]);
                if (new_i == -1)
                    break;
                i = new_i;
                i++;
                continue;
            }
        }
        if (s[i] == ' ')
        {
            if (s[i + 1] && (s[i + 1] == '"' || s[i + 1] == '\''))
            {
                if (s[i + 2] && s[i + 2] == s[i + 1])
                {
                    if (s[i + 3] == ' ' || s[i + 3] == '\0')
                    {
                        s = remove_empty_quotes_arg(s, i + 1);
                        if (!s)
                            return (NULL);
                        i = 0;
                        continue;
                    }
                }
            }
        }
        if ((s[i] == '"' || s[i] == '\'') && s[i + 1] && s[i + 1] == s[i])
        {
            s = remove_empty_quotes(s, i);
            if (!s)
                return (NULL);
            if (cmd && cmd->num_tokens > 0)
                cmd->num_tokens--;
            i = 0;
            continue;
        }
        i++;
    }
    return (s);
}


char *delete_quotes(char *str, char c)
{
    int len = 0, i = 0, j = 0;
    while (str[i])
        if (str[i++] != c)
            len++;
    char *temp = malloc(len + 1);
    if (!temp)
        exit_error("malloc failed", 1);

    i = 0;
    while (str[i])
    {
        if (str[i] != c)
            temp[j++] = str[i];
        i++;
    }
    temp[j] = '\0';
    free(str);
    return temp;
}
