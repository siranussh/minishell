/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:16:38 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 00:44:38 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	split_tokens(char *str, char **token, int max_tokens)
// {
// 	int	pos;
// 	int	start;
// 	int	i;

// 	pos = 0;
// 	start = 0;
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i + 1]
// 			&& str[i + 1] != ' ')
// 			start = i + 1;
// 		if (str[i] == 34 || str[i] == 39)
// 			i = find_closing_quote(i + 1, str, str[i]);
// 		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
// 			&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
// 		{
// 			if (pos >= max_tokens)
// 				exit_error("minishell: token overflow", 1);
// 			token[pos] = ft_substr(str, start, i - start + 1);
// 			if (token[pos] == NULL)
// 				exit_error("minishell: malloc failed", 1);
// 			pos++;
// 		}
// 	}
// 	token[pos] = NULL;
// 	return (i);
// }

static void	add_tok(char **token, int *pos, char *str, int range[2])
{
	int	start;
	int	end;

	start = range[0];
	end = range[1];
	token[*pos] = ft_substr(str, start, end - start + 1);
	if (!token[*pos])
		exit_error("minishell: malloc failed", 1);
	(*pos)++;
}

static int	split_tokens(char *str, char **token, int max_tokens)
{
	int	i;
	int	pos;
	int	range[2];

	i = -1;
	pos = 0;
	range[0] = 0;
	while (str[++i])
	{
		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			&& str[i + 1] && str[i + 1] != ' ')
			range[0] = i + 1;
		if (str[i] == '"' || str[i] == '\'')
			i = find_closing_quote(i + 1, str, str[i]);
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
			&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			if (pos >= max_tokens)
				exit_error("minishell: token overflow", 1);
			range[1] = i;
			add_tok(token, &pos, str, range);
		}
	}
	token[pos] = NULL;
	return (i);
}

static char	**get_token_arr(t_data *data, char *str, t_cmd *cmd)
{
	char	**token;
	char	*temp;
	char	*trimmed;
	int		temp_allocated;

	temp = str;
	temp_allocated = 0;
	if (check_quotes_type(temp) == -1)
	{
		trimmed = ft_strtrim(temp, " ");
		if (!trimmed)
			exit_error("minishell: malloc failed", 1);
		temp = skip_empty_quotes(trimmed, cmd);
		free(trimmed);
		temp_allocated = 1;
	}
	token = ft_calloc((size_t)(cmd->num_tokens + 1), sizeof(char *));
	if (!token)
		exit_error("minishell: malloc failed", 1);
	data->total_chars += split_tokens(temp, token, cmd->num_tokens);
	if (temp_allocated)
		free(temp);
	return (token);
}

t_cmd	*build_cmd(t_data *data, char *line)
{
	t_cmd	*temp;
	char	**old_tokens;

	temp = init_cmd(data, line);
	if (temp->num_tokens > 0)
		temp->tokens = get_token_arr(data, line + data->total_chars, temp);
	else
		temp->tokens = NULL;
	if (temp->cmd != NULL)
	{
		old_tokens = temp->tokens;
		temp->tokens = join_cmd_tokens(temp->cmd, temp->tokens,
				temp->num_tokens);
		if (old_tokens != temp->tokens)
			ft_free(old_tokens);
	}
	if (!check_invalid_redirections(temp))
	{
		data->p->exit_code = 2;
		free_cmd_list(temp);
		return (NULL);
	}
	normalize_redirections(temp);
	return (temp);
}
