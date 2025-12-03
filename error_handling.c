/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:42:53 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/04 00:01:41 by sihakoby         ###   ########.fr       */
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
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (file)
	{
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (err)
		ft_putendl_fd(err, STDERR_FILENO);
	else
		ft_putstr_fd("\n", STDERR_FILENO);
}
