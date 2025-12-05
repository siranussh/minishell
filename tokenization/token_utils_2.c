/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:58:23 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 00:44:54 by sihakoby         ###   ########.fr       */
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


static char	*extract_command(t_data *data, char *line)
{
	int		i;
	int		start;
	char	*str;

	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	start = i;
	while (line[i] && line[i] != 32 && !(line[i] >= 9 && line[i] <= 13)
		&& !is_other_op(line[i]))
	{
		if (line[i] == 34 || line[i] == 39)
			i = find_closing_quote(i + 1, line, line[i]);
		i++;
	}
	if (i && !is_other_op(line[i]))
		str = ft_substr(line, start, i - start);
	else
		str = NULL;
	data->total_chars += i;
	return (str);
}

t_cmd	*init_cmd(t_data *data, char *line)
{
	t_cmd	*temp;

	temp = calloc(1, sizeof(t_cmd));
	if (!temp)
		exit_error("minishell: malloc failed", 1);
	temp->cmd = extract_command(data, line + data->total_chars);
	temp->num_tokens = count_tokens(line + data->total_chars);
	temp->next = NULL;
	temp->flags = data->flags;
	temp->redirs = NULL;
	temp->infile = NULL;
	temp->outfile = NULL;
	temp->append = 0;
	temp->heredoc = 0;
	temp->delimiter = NULL;
	temp->fd_in = -1;
	temp->fd_out = -1;
	return (temp);
}