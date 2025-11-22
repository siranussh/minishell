/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 21:20:29 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/22 22:08:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

extern int	g_exit_code;

void	set_status(int status)
{
	g_exit_code = status;
}

int	get_status(void)
{
	return (g_exit_code);
}
