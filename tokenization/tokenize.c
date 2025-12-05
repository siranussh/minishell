/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:13:37 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 12:23:56 by anavagya         ###   ########.fr       */
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

int	check_invalid_redirections(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->tokens)
		return (1);
	i = 0;
	while (cmd->tokens[i])
	{
		if ((ft_strncmp(cmd->tokens[i], "<<", 2) == 0 && ft_strlen(cmd->tokens[i]) > 2) ||
			(ft_strncmp(cmd->tokens[i], ">>", 2) == 0 && ft_strlen(cmd->tokens[i]) > 2))
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", cmd->tokens[i]);
			return (0);
		}
		else if (ft_strcmp(cmd->tokens[i], "<>") == 0 ||
			ft_strcmp(cmd->tokens[i], "><") == 0)
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", cmd->tokens[i]);
			return (0);
		}
		else if ((ft_strcmp(cmd->tokens[i], "<") == 0 || ft_strcmp(cmd->tokens[i], ">") == 0) &&
		(!cmd->tokens[i + 1] || cmd->tokens[i + 1][0] == '<' || cmd->tokens[i + 1][0] == '>'))
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", cmd->tokens[i]);
			return (0);
		}
		else if ((ft_strcmp(cmd->tokens[i], "<<") == 0 || ft_strcmp(cmd->tokens[i], ">>") == 0) &&
		(!cmd->tokens[i + 1] || cmd->tokens[i + 1][0] == '<' || cmd->tokens[i + 1][0] == '>'))
		{
			fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", cmd->tokens[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	tokenize(t_data *data, t_cmd **cmd, char *read_line)
{
	int		i;
	t_cmd	*temp;
	char	**lines;

	i = 0;
	lines = NULL;
	data->total_chars = 0;
	if (parse_line(&data, read_line, &lines))
		return (0);
	*cmd = build_cmd(data, lines[0]);
	expand(cmd, data);
	while (++i <= data->flags->pipe)
	{
		data->total_chars = 0;
		temp = build_cmd(data, lines[i]);
		if (!temp)
		{
			free_cmd_list(*cmd);
			*cmd = NULL;
			break;
		}
		expand(&temp, data);
		if (!cmd || !(*cmd))///
			return (0);///
		(last_cmd(cmd))->next = temp;
		temp = temp->next;
	}
	while (i--)
		free(lines[i]);
	free(lines);
	return (1);
}
