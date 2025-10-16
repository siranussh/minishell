/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:56 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/16 22:53:52 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	execute(char **args, int cmd_count, t_env *env)
{
	t_cmd	*cmds;
	t_pipe	*p;

	init_pipe_struct(cmds);
	if (!args || !*args)
		return (0);
	if (cmd_count == 1)
		execute_single_command(args, env);
	// execute_pipeline()
}
