/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:18:46 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/28 13:39:49 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenization.h"
# include "builtins.h"
# include "execution.h"
# include "expansion.h"

# include <stdio.h>
# include <stdlib.h> // exit()
# include <limits.h>
# include <stddef.h>
# include <unistd.h> // getcwd() chdir() execve() access() unlink()
# include <dirent.h> // opendir() closedir()
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
#include <termios.h>

# include "../libft/libft.h"

# include <aio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h> // waitpid()
# include <fcntl.h>

extern int	g_exit_code;

// get_status.c
void	set_status(int status);
int		get_status(void);

// free.c
void	ft_free(char **str);
void	free_redirs(t_redir *redir);
void	free_env_list(t_env *head);
void	free_flags(t_flags *flags);
void	free_data(t_data *data);

//signal.c
void    setup_signals_parent_exec(void);
void    sigint_handler(int signo);
#endif
