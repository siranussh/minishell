/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:12:11 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:55:00 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

t_pipe	*init_pipe_struct(t_cmd *cmds)
{
	t_pipe	*p;

	p = (t_pipe *)malloc(sizeof(t_pipe));
	if (!p)
		return (NULL);
	p->prev_fd = -1;
	p->exit_code = 0;
	p->cmds_count = ft_cmd_size(cmds);
	if (p->cmds_count <= 0)
		return (free(p), NULL);
	p->pids = (int *)malloc(sizeof(int) * p->cmds_count);
	if (!p->pids)
	{
		free(p);
		return (NULL);
	}
	return (p);
}

t_redir	*init_redir(int type, char *filename)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->filename = ft_strdup(filename);
	r->next = NULL;
	return (r);
}
