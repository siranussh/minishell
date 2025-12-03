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

t_pipe	*init_pipe_struct(t_data *data)
{
	// t_pipe	*p;

	// p = (t_pipe *)malloc(sizeof(t_pipe));
	// if (!p)
	// 	return (NULL);
	data->p->prev_fd = -1;
	data->p->exit_code = 0;
	data->p->cmds_count = ft_cmd_size(data->cmd);
	if (data->p->cmds_count <= 0)
		return (free(data->p), NULL);
	data->p->pids = (int *)malloc(sizeof(int) * data->p->cmds_count);
	if (!data->p->pids)
	{
		free(data->p);
		return (NULL);
	}
	return (data->p);
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
