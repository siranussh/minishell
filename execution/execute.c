/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:56 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/22 23:48:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	is_pipeline(char *line)
{
	int	i;

	i = 0;
	if (!line || !line)
		return (0);
	while (line[i])
	{
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int	execute(char **args, char *line, t_env *env)
{
	t_cmd	*cmds;
	t_pipe	*p;

	//tokenize() 
	init_pipe_struct(cmds);
	if (!args || !*args)
		return (0);
	if (!is_pipeline(line))/////////
		execute_single_command(args, env);//////////
	else
	{
		cmds = store_cmds(args);
		p = init_pipe_struct(cmds);
		execute_pipeline(cmds, env, p);
		free(p);
	}
}
