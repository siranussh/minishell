/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:42:53 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/13 16:15:20 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_error(char *str, int code)
{
	printf("%s\n", str);
	exit(code);
}

void	print_error(char *name, char *file, char *err)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	if (file)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (err)
		ft_putendl_fd(err, 2);
	else
		ft_putstr_fd("\n", 2);
}
