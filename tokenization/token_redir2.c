/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 13:04:27 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/07 15:24:29 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_tokens(t_cmd *cmd)
{
	int	i;
	int	type;

	i = 0;
	if (!cmd || !cmd->tokens)
		return ;
	while (cmd->tokens[i])
	{
		type = redir_type(cmd->tokens[i]);
		if (type)
		{
			if (cmd->tokens[i + 1])
				cmd->tokens = remove_token(cmd->tokens, i + 1);
			cmd->tokens = remove_token(cmd->tokens, i);
			continue ;
		}
		i++;
	}
}

static void	handle_redir(char **res, char *tok, int *i, int *idx)
{
	if (tok[*i + 1] && tok[*i + 1] == tok[*i])
	{
		res[*idx] = ft_substr(tok, *i, 2);
		(*idx)++;
		*i += 2;
	}
	else
	{
		res[*idx] = ft_substr(tok, *i, 1);
		(*idx)++;
		(*i)++;
	}
}

static void	process_redir_segment(char **res, char *tok, int *i, int *idx)
{
	int		start;
	char	quote;

	start = *i;
	quote = 0;
	while (tok[*i])
	{
		if (!quote && (tok[*i] == '\'' || tok[*i] == '"'))
			quote = tok[*i];
		else if (tok[*i] == quote)
			quote = 0;
		if (!quote && (tok[*i] == '<' || tok[*i] == '>'))
			break ;
		(*i)++;
	}
	if (*i > start)
	{
		res[*idx] = ft_substr(tok, start, *i - start);
		(*idx)++;
	}
	if (tok[*i] && !quote && (tok[*i] == '<' || tok[*i] == '>'))
		handle_redir(res, tok, i, idx);
}

char	**split_redirs_token(char *tok, int *count)
{
	char	**res;
	int		cap;
	int		idx;
	int		i;

	cap = 4;
	idx = 0;
	i = 0;
	res = malloc(sizeof(char *) * cap);
	if (!res)
		return (NULL);
	while (tok[i])
	{
		if (idx + 3 >= cap)
		{
			cap *= 2;
			res = realloc(res, sizeof(char *) * cap);
		}
		process_redir_segment(res, tok, &i, &idx);
	}
	res[idx] = NULL;
	*count = idx;
	return (res);
}
