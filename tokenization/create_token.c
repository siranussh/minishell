/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:16:38 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/03 19:37:04 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_tokens(char *str, char **token)
{
	int	pos;
	int	start;
	int	i;

	pos = 0;
	start = 0;
	i = -1;
	while (str[++i])
	{
		if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i + 1]
			&& str[i + 1] != ' ')
			start = i + 1;
		if (str[i] == 34 || str[i] == 39)
			i = find_closing_quote(i + 1, str, str[i]);
		if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13)
			&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
		{
			token[pos] = ft_substr(str, start, i - start + 1);
			if (token[pos] == NULL)
				exit_error("minishell: malloc failed", 1);
			pos++;
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
	token = malloc(sizeof(char *) * (cmd->num_tokens + 1));
	if (!token)
		exit_error("minishell: malloc failed", 1);
	data->total_chars += split_tokens(temp, token);
	if (temp_allocated)
		free(temp);
	return (token);
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
	normalize_redirections(temp);
	return (temp);
}

// best version 28.11.25
// t_cmd	*build_cmd(t_data *data, char *line)
// {
// 	t_cmd	*temp;

// 	temp = calloc(1, sizeof(t_cmd));
// 	if (!temp)
// 		exit_error("minishell: malloc failed", 1);
// 	temp->cmd = extract_command(data, line + data->total_chars);
// 	temp->num_tokens = count_tokens(line + data->total_chars);
// 	temp->next = NULL;
// 	temp->flags = data->flags;
// 	// if (temp->num_tokens == 0)
// 	// 	return (temp);
// 	temp->redirs = NULL;//aniiiiiiii newwwwwwwwww
// 	temp->infile = NULL;//aniiiiiiiiiiiiiiiiii
// 	temp->outfile = NULL;
// 	temp->append = 0;
// 	temp->heredoc = 0;
// 	temp->delimiter = NULL;
// 	temp->fd_in = -1;
// 	temp->fd_out = -1;
// 	temp->next = NULL;//aniiiiiiiiii
// 	if (temp->num_tokens > 0)
// 		temp->tokens = get_token_arr(data, line + data->total_chars, temp);
// 	else
// 		temp->tokens = NULL;
// 	if (temp->cmd != NULL)///////////ani
// 		temp->tokens = join_cmd_tokens(temp->cmd, temp->tokens,
// temp->num_tokens);//ani
// 	normalize_redirections(temp);
// 	return (temp);
// }
