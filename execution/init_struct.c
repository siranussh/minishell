/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:59:31 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:59:31 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipe	*init_pipe_struct(t_data *data)
{
	data->p->prev_fd = -1;
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
