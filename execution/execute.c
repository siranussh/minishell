/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:56 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 11:44:56 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	execute(char **args, int cmd_count, t_env *env)
{
	if (!args || !*args)
		return (0);
	if (cmd_count == 1)
		execute_single_command(args, env);
}
