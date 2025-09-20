/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:10:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/20 19:36:01 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

# include <aio.h>
# include <unistd.h> //getcwd() chdir()
# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

// list_utils.c
t_env	*ft_lstnew(char *name, char *value);
void	ft_lstadd_back(t_env **lst, t_env *new);
void	free_env_list(t_env *head);

// utils.c
int		ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, int start, int len);

// builtins.c
int		check_built_in_type(char **args, char **envp);

// echo.c
int		built_in_echo(char **args);

// pwd.c
int		built_in_pwd(void);

// env_parsing.c
int		return_name_size(char *arg);
char	*return_name(char *arg);
char	*return_value(char *arg);
t_env	*env_parse(char **envp);

// env.c
int		built_in_env(t_env *env);

// cd .c
char	*get_env_values(t_env *env, char *key);
int	built_in_cd(int argc, char **args, t_env *env);

// int	built_in_export(char **args);
// int	built_in_unset(char **args);
// int	built_in_exit(char **args);

#endif
