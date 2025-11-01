/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:18:46 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/01 12:06:33 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenization.h"
# include "builtins.h"
# include "execution.h"

# include <stdio.h>
# include <stdlib.h> // exit()
# include <stddef.h>
# include <unistd.h> // getcwd() chdir() execve() access() unlink()
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include "../libft/libft.h"

# include <aio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h> // waitpid()
# include <fcntl.h>

extern int	g_exit_code;

#endif
