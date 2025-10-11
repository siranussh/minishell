/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 22:45:40 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/12 00:20:45 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

t_cmd	*store_cmds(char **args)
{
	int		i;
	t_cmd	*head;
	

	if (!args || !*args)
		return (NULL);
	i = 0;
	while (args[i])
	{
		
	}
	return (head);
}

// For pipeline I'll receive char ** with cmd segments
// echo hi | grep h | wc -l
//
// result[0] = "echo hi ";
// result[1] = " grep h ";
// result[2] = " wc -l";
// result[3] = NULL;
