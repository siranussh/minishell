/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:18:46 by sihakoby          #+#    #+#             */
/*   Updated: 2025/11/25 23:28:18 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "tokenization.h"
# include "builtins.h"
# include "execution.h"

# include <stdio.h>
# include <stdlib.h> // exit()
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

#endif
