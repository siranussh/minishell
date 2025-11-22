/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 20:40:53 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 21:37:59 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

//*************//
//*    NEW    *//
//*************//

void	parse_redirs_new(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->tokens)
		return ;
	while (cmd->tokens[i])
	{
		if (strcmp(cmd->tokens[i], "<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_IN, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], "<<") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_HEREDOC, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_OUT, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		else if (strcmp(cmd->tokens[i], ">>") == 0 && cmd->tokens[i + 1])
		{
			add_redir_back(&cmd->redirs, init_redir(REDIR_APPEND, cmd->tokens[i+1]));
			cmd->tokens = remove_tokens_from_array(cmd->tokens, i, 2);
			continue ;
		}
		i++;
	}
}