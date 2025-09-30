/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:10:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/30 16:25:13 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft.h"
# include <aio.h>
# include <unistd.h> //getcwd() chdir()
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// list_utils.c
t_env	*ft_env_new(char *key, char *value);
void	ft_env_add_back(t_env **lst, t_env *new);
int		ft_env_size(t_env *env);
void	del_env_node(t_env *prew);
void	free_env_list(t_env *head);

// utils.c
int		ft_strlen_ms(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr_ms(char const *s, int start, int len);
char	*ft_strcpy(char *dest, char *src);

// free.c
void	ft_free(char **str);

// builtins.c
int		check_built_in_type(int argc, char **args, char **envp);

// echo.c
int		built_in_echo(char **args);

// pwd.c
int		built_in_pwd(void);

// env_parsing.c
int		return_key_size(char *arg);
// char	*return_key(char *arg, int (*size_funct)(char *));
// char	*return_value(char *arg, int (*size_funct)(char *));
char	*return_key(char *arg);
char	*return_value(char *arg);
t_env	*env_parse(char **envp);

// env.c
int		built_in_env(t_env *env);

// cd .c
char	*get_env_values(t_env *env, char *key);
int		change_env_value(t_env *env, char *key, char *value);
int		cd_helper(char *path, char *old_pwd, t_env *env);
int		built_in_cd(int argc, char **args, t_env *env);

// unset.c
int		get_env_key_index(t_env *env, char *key);
int		built_in_unset(char **args, t_env **env);

// unset -> exit -> export;
//
// exit.c
// int	built_in_exit(char **args);

// export.c
char	*if_env_value_exist(t_env *env, char *key);
int		return_key_size_export(char *arg);
char	*return_key_export(char *arg);
char	*return_value_export(char *arg);
int		built_in_export(char **args, int argc, t_env **env);

#endif
