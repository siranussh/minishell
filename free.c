/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:23:46 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:27:15 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_lines(char **lines)
{
	int	i;

	i = 0;
	if (!lines)
		return ;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_flags(t_flags *flags)
{
	if (!flags)
		return ;
	free(flags);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->cmd)
		free_cmd_list(data->cmd);
	if (data->flags)
		free_flags(data->flags);
	if (data->p)
		free_pipe_struct(data->p);
	if (data->env)
		free_env_list(data->env);
	if (data->env_exp)
		free_env_exp(&data->env_exp);
	free(data);
}

void	free_pipe_struct(t_pipe *p)
{
	if (p)
	{
		if (p->pids)
			free(p->pids);
		free(p);
	}
}
