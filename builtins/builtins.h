/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:10:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/08/27 17:24:27 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	check_built_in_type(char **arg);
int	built_in_echo(char **args);
int	built_in_cd(char **args);
int	built_in_pwd(char **args);
int	built_in_export(char **args);
int	built_in_unset(char **args);
int	built_in_env(char **args);
int	built_in_exit(char **args);

#endif
