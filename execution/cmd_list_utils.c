/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:03:51 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/04 12:03:53 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cmd_size(t_cmd *cmds)
{
	int	count;

	count = 0;
	while (cmds != NULL)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
