/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:10:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/06 13:48:32 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <aio.h>
# include <unistd.h>
# include <stdio.h>

// typedef s_list
// {}

/// util.c
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, int n);

// builtins.c
int		check_built_in_type(char **arg);

// echo.c
int		is_n_flag(char *str);
int		built_in_echo(char **args);
int		check_n_flag(char **args);

// pwd.c
int		built_in_pwd(void);

// int	built_in_cd(char **args);
// int	built_in_export(char **args);
// int	built_in_unset(char **args);
// int	built_in_env(char **args);
// int	built_in_exit(char **args);

#endif
