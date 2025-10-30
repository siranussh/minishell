/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:18:46 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/30 18:12:42 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenization.h"
# include "builtins.h"
# include "execution.h"

#include <stdio.h>
#include <stdlib.h> // exit()
#include <stddef.h>
#include <unistd.h> // getcwd() chdir() execve() access() unlink()
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

# include "../libft/libft.h"

# include <aio.h>
# include <string.h>
# include <errno.h>
#include <sys/wait.h> // waitpid()
# include <fcntl.h>

extern int g_exit_code;

#endif