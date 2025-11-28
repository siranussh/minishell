/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:42:47 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/28 14:35:29 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_tokens(char *str)
{
    int i = 0;
    int count = 0;

    while (str[i])
    {
        while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
            i++;
        if (!str[i])
            break;
        count++;
        while (str[i] && str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
        {
            if (str[i] == '"' || str[i] == '\'')
                i = find_closing_quote(i + 1, str, str[i]) + 1;
            else
                i++;
        }
    }
    return count;
}

int	check_redir(char **tk, int i)
{
	char	*temp;
	int		j;

	j = 0;
	if (redir_type(tk[i]) == -1)
		return (redir_error());
	temp = ft_strchr(tk[i], redir_smb(redir_type(tk[i])));
	while (temp && redir_type(temp + j))
	{
		j = 0;
		while (temp[j] && (temp[j] == 32 || is_other_op(temp[j])))
			j++;
		if ((redir_type(tk[i]) && !temp[j]) || is_other_op(temp[ft_strlen(temp)
					- 1]))
			return (redir_error());
		temp = ft_strchr(temp + j, redir_smb(redir_type(temp + j)));
	}
	return (0);
}

int	parse_line(t_data **data, char *line, char ***tokens_by_pipe)
{
	(*data)->flags->quote = check_dquote(line, 2, 2, (*data));
	if ((*data)->flags->quote == 0)
	{
		free(line);
		return (1);
	}
	(*data)->flags->pipe = count_pipes(line);
	if ((*data)->flags->pipe == -1)
	{
		free(line);
		return (1);
	}
	*tokens_by_pipe = split_pipes(line);
	if (!(*tokens_by_pipe))
	{
		free(line);
		return (1);
	}
	return (0);
}

t_cmd	*last_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

int count_tokens_array(char **tokens)
{
int count = 0;

if (!tokens)
    return 0;

while (tokens[count])
    count++;

return count;
}
