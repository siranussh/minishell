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

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	execute(char **args, t_env *env)
{
	t_cmd	*cmds;
	t_pipe	*p;

	init_pipe_struct(cmds);
	if (!args || !*args)
		return (0);
	if (!is_pipeline)
		execute_single_command(args, env);
	else
	{
		cmds = store_cmds(args);
		p = init_pipe_struct(cmds);	
		execute_pipeline(cmds, env, p);
		free(p);
	}
}
