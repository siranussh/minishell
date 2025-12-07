/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 15:33:47 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 15:34:26 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_data	*init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_error("minishell: malloc failed", 1);
	data->env = NULL;
	data->flags = ft_calloc(1, sizeof(t_flags));
	if (!data->flags)
		exit_error("minishell: malloc failed", 1);
	data->p = ft_calloc(1, sizeof(t_pipe));
	if (!data->p)
		exit_error("minishell: malloc failed", 1);
	data->p->pids = NULL;
	data->flags->pipe = 0;
	data->flags->quote = 0;
	data->flags->has_special = 0;
	data->cmd = NULL;
	data->total_chars = 0;
	return (data);
}

t_data	*init_shell(char **envp)
{
	t_data	*data;
	t_env	*env;

	data = init();
	if (!data)
		exit_error("minishell: malloc failed", 1);
	env = env_parse(envp);
	data->env = env;
	data->env_exp = env_exp_from_list(env);
	if (!data->env_exp)
		exit_error("minishell: malloc failed", 1);
	return (data);
}
