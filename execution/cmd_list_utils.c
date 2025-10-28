/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:40:29 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/28 14:19:58 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

t_cmd	*ft_cmd_new(char **args)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd_line = cpy_str_arr(args);
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->append = 0;
	new_node->heredoc = 0;
	new_node->delimiter = NULL;
	new_node->fd_in = -1;
	new_node->fd_out = -1;
	new_node->next = NULL;
	return (new_node);
}

void	ft_cmd_add_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*current;

	current = *lst;
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

int	ft_cmd_size(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
