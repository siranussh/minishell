/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:13:37 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 19:31:08 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_heredoc(char *tok)
{
	if (!tok)
		return (0);
	return (tok[0] == '<' && tok[1] == '<' && tok[2] == '\0');
}

int	token_is_heredoc_delimiter(char **tokens, int i)
{
	if (!tokens || !tokens[i])
		return (0);
	if (i == 0)
		return (0);
	return (is_heredoc(tokens[i - 1]));
}

static int	print_syntax_error(char *token)
{
	fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
		token);
	return (0);
}

static int	is_invalid_token(char **tokens, int i)
{
	if ((ft_strncmp(tokens[i], "<<", 2) == 0 && tokens[i][2] == '<')
		|| (ft_strncmp(tokens[i], ">>", 2) == 0 && tokens[i][2] == '>'))
		return (1);
	if (ft_strcmp(tokens[i], "<>") == 0 || ft_strcmp(tokens[i], "><") == 0)
		return (1);
	if ((ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">") == 0)
		&& (!tokens[i + 1] || tokens[i + 1][0] == '<'
		|| tokens[i + 1][0] == '>'))
		return (1);
	if ((ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i], ">>") == 0)
		&& (!tokens[i + 1] || tokens[i + 1][0] == '<'
		|| tokens[i + 1][0] == '>'))
		return (1);
	return (0);
}

int	check_invalid_redirections(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->tokens)
		return (1);
	i = 0;
	while (cmd->tokens[i])
	{
		if (is_invalid_token(cmd->tokens, i))
			return (print_syntax_error(cmd->tokens[i]));
		i++;
	}
	return (1);
}

// int	tokenize(t_data *data, t_cmd **cmd, char *read_line)
// {
// 	int		i;
// 	t_cmd	*temp;
// 	char	**lines;

// 	i = 0;
// 	lines = NULL;
// 	data->total_chars = 0;
// 	if (parse_line(&data, read_line, &lines))
// 		return (0);
// 	*cmd = build_cmd(data, lines[0]);
// 	if (!*cmd)
// 	{
// 		while (i--)
// 		free(lines[i]);
// 		free(lines);
// 			return (0);
// 	}
// 	expand(cmd, data);

// 	while (++i <= data->flags->pipe)
// 	{
// 		data->total_chars = 0;
// 		temp = build_cmd(data, lines[i]);
// 		if (!temp)
// 		{
// 			free_cmd_list(*cmd);
// 			*cmd = NULL;
// 			break;
// 		}
// 		expand(&temp, data);
// 		if (!cmd || !(*cmd))
// 			return (0);
// 		(last_cmd(cmd))->next = temp;
// 		temp = temp->next;
// 	}
// 	while (i--)
// 		free(lines[i]);
// 	free(lines);
// 	return (1);
// }

void	free_lines(char **lines, int count)
{
	while (count--)
		free(lines[count]);
	free(lines);
}

int	tokenize(t_data *data, t_cmd **cmd, char *read_line)
{
	int		i;
	t_cmd	*temp;
	char	**lines;

	i = 0;
	data->total_chars = 0;
	if (parse_line(&data, read_line, &lines))
		return (0);
	*cmd = build_cmd(data, lines[0]);
	if (!*cmd)
		return (free_lines(lines, 1), 0);
	expand(cmd, data);
	while (++i <= data->flags->pipe)
	{
		data->total_chars = 0;
		temp = build_cmd(data, lines[i]);
		if (!temp)
			return (free_cmd_list(*cmd), free_lines(lines, i + 1),
				*cmd = NULL, 0);
		expand(&temp, data);
		(last_cmd(cmd))->next = temp;
	}
	free_lines(lines, i);
	return (1);
}
