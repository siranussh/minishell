/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:49:17 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:27:51 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	add_redir_back(t_redir **list, t_redir *new)
{
	t_redir	*tmp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

// void	build_redir_list(t_cmd *cmd)
// {
// 	if (cmd->infile)
// 		add_redir_back(&cmd->redirs, init_redir(1, cmd->infile));
// 	if (cmd->heredoc && cmd->delimiter)
// 		add_redir_back(&cmd->redirs, init_redir(2, cmd->delimiter));
// 	if (cmd->outfile)
// 	{
// 		if (cmd->append == 2)
// 			add_redir_back(&cmd->redirs, init_redir(4, cmd->outfile));
// 		else
// 			add_redir_back(&cmd->redirs, init_redir(3, cmd->outfile));
// 	}
// }

char	**remove_tokens_from_array(char **tokens, int start, int count)
{
	int		i;
	int		j;
	int		old_len;
	int		new_len;
	char	**new_tokens;

	i = 0;
	j = 0;
	old_len = 0;
	if (!tokens)
		return (NULL);
	while (tokens[old_len])
		old_len++;
	new_len = old_len - count;
	if (new_len <= 0)
	{
		new_tokens = malloc(sizeof(char *));
		new_tokens[0] = NULL;
		return (new_tokens);
	}
	new_tokens = malloc(sizeof(char *) * (new_len + 1));
	if (!new_tokens)
		return (NULL);
	i = 0;
	j = 0;
	while (i < old_len)
	{
		if (i >= start && i < start + count)
		{
			free(tokens[i]);
			i++;
			continue;
		}
		new_tokens[j++] = tokens[i++];
	}
	new_tokens[j] = NULL;
	free(tokens);
	return (new_tokens);
}
