/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:27:50 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/26 22:59:33 by sihakoby         ###   ########.fr       */
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

char *skip_empty_quotes(char *str, t_cmd *cmd)
{
(void)cmd;
if (!str)
return NULL;
int len = strlen(str);
char *res = malloc(len + 1);
if (!res)
    exit_error("malloc failed", 1);

int i = 0, j = 0;
while (str[i])
{
    if (str[i] == '"' && str[i + 1] == '"')
    {
        i += 2;
        continue;
    }
    if (str[i] == '\'' && str[i + 1] == '\'')
    {
        i += 2;
        continue;
    }
    res[j++] = str[i++];
}
res[j] = '\0';
return res;
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
