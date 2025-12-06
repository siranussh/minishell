/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:18:46 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 22:30:53 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef MINISHELL_H
# define MINISHELL_H

# define FAILURE 1
# define INTERACTIVE 1
# define NINTERACTIVE 2
# define HEREDOC 3

# include "tokenization.h"
# include "builtins.h"
# include "execution.h"
# include "expansion.h"

# include <sys/ioctl.h>

# include <stdio.h>
# include <stdlib.h> // exit()
# include <limits.h>
# include <stddef.h>
# include <unistd.h> // getcwd() chdir() execve() access() unlink()
# include <dirent.h> // opendir() closedir()
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# include "../libft/libft.h"

# include <aio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h> // waitpid()
# include <fcntl.h>

extern int	g_exit_code;

// utils.c
int			skip_spaces(char *str, int i);
char		*str_tolower(char *str);
char		*unqoute_str(char *str);
int			check_spaces(char *str);

// arr_list_handler.c
char		*ft_strjoin_three(char *s1, char *s2, char *s3);
void		refresh_env_exp(t_data *data);
int			built_in_export_wrapper(char **args, int argc, t_data *data);
int			built_in_unset_wrapper(char **args, t_data *data);
char		*expand_var(t_data *data, char *key);

// arr_list_handler2.c
t_env_exp	*env_exp_from_list(t_env *env_list);

// free_env_exp.c
void		free_env_exp(t_env_exp **env_exp_ptr);

// free_cmd.c
void		free_redirs(t_redir *redir);
void		free_cmd_list(t_cmd *cmd);

// free.c
void		ft_free(char **str);
void		free_env_list(t_env *head);
void		free_flags(t_flags *flags);
void		free_data(t_data *data);
void		free_pipe_struct(t_pipe *p);

//signal.c
void		setup_signals_parent_exec(void);
void		setup_signals(void);
void		set_default_signals(void);
void		check_interactive_sigint(t_data *data);

// error_handling.c
int			exit_error(char *str, int code);
void		print_error(char *name, char *file, char *err);

// error_wrappers.c
int			pipe_syntax_error(t_data *data);
int			quote_error(t_data *data);
int			redir_error(void);
int			export_error(char *arg);
int			shlvl_error(char *arg);

// minishell.c
t_data		*init(void);
void		unquote_all_tokens(t_cmd *cmd);

#endif
