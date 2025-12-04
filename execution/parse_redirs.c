/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 10:56:00 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/03 10:56:00 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	handle_in_redir(t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd->tokens[i], "<") == 0 && cmd->tokens[i + 1])
	{
		add_redir_back(&cmd->redirs,
			init_redir(REDIR_IN, cmd->tokens[i + 1]));
		cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		return (1);
	}
	return (0);
}

static int	handle_heredoc_redir(t_cmd *cmd, int i)
{
	t_redir	*r;
	char	*tok;
	char	*tmp;

	if (ft_strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
	{
		tok = cmd->tokens[i + 1];
		if ((tok[0] == '"' && tok[ft_strlen(tok) - 1] == '"')
			|| (tok[0] == '\'' && tok[ft_strlen(tok) - 1] == '\''))
		{
			r = init_redir(REDIR_HEREDOC,
					ft_substr(tok, 1, ft_strlen(tok) - 2));
			r->quoted_delimiter = 1;
		}
		else
		{
			tmp = ft_strdup(tok);
			r = init_redir(REDIR_HEREDOC, tmp);
			free(tmp);
			r->quoted_delimiter = 0;
		}
		add_redir_back(&cmd->redirs, r);
		cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		return (1);
	}
	return (0);
}

static int	handle_out_redir(t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
	{
		add_redir_back(&cmd->redirs,
			init_redir(REDIR_OUT, cmd->tokens[i + 1]));
		cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		return (1);
	}
	return (0);
}

static int	handle_append_redir(t_cmd *cmd, int i)
{
	if (ft_strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
	{
		add_redir_back(&cmd->redirs,
			init_redir(REDIR_APPEND, cmd->tokens[i + 1]));
		cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
		return (1);
	}
	return (0);
}

void	parse_redirs(t_cmd *cmd)
{
	int	i;

	if (!cmd || !cmd->tokens)
		return ;
	if (!has_redirs(cmd->tokens))
		return ;
	i = 0;
	while (cmd->tokens[i])
	{
		if (handle_in_redir(cmd, i) || handle_heredoc_redir(cmd, i)
		|| handle_out_redir(cmd, i) || handle_append_redir(cmd, i))
			continue ;
		i++;
	}
}
