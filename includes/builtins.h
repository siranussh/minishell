/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:16:42 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/28 22:13:28 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef BUILTINS_H
# define BUILTINS_H

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

// builtin_utils.c
int		ft_strlen_ms(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr_ms(char const *s, int start, int len);
// char	*ft_strcpy(char *dest, char *src);

// builtins.c
int		is_built_in(char **args);
int 	run_built_in(int argc, char **args, t_data *data);

// echo.c
int		built_in_echo(char **args);

// pwd.c
int		built_in_pwd(void);

// env_parsing.c
int		return_key_size(char *arg);
char	*return_key(char *arg);
char	*return_value(char *arg);
t_env	*env_parse(char **envp);

// env.c
int		built_in_env(int argc, char **args, t_env *env);

// cd_utils.c
char	*get_env_values(t_env *env, char *key);
int		change_env_value(t_env *env, char *key, char *value);

// cd.c
int		cd_helper(char *path, char *old_pwd, t_env *env);
void	cd_minus(char *old_pwd, int *status, t_env *env);
void	cd_with_argument(char **args, char *old_pwd, int *status, t_env *env);
int		built_in_cd(int argc, char **args, t_env *env);

// unset.c
int		get_env_key_index(t_env *env, char *key);
int		built_in_unset(char **args, t_env **env);

// exit.c
int		built_in_exit(int argc, char **args);

// exit_utils.c
int		is_number(char *arg);
int		is_long_overflow(char *s);
long	ft_atol(const char *str);

// export_utils.c
void	update_env_value(t_env **env, char *key, char *value);
void	key_existance(t_env **env, char *key, char *value);
int		is_valid_identifier(char *arg);
void	handle_export_arg(t_env **env, char *arg);
void	print_export(char **env_arr, t_env **env);

// export_append.c
void	giving_new_value(t_env **env, char *key, char *value);
void	append_export(t_env **env, char *key, char *value);

// export_sort.c
char	**convert_to_array(t_env *env);
void	sort_in_alpha_order(char **env_arr);

// export.c
char	*if_env_value_exist(t_env *env, char *key);
int		return_key_size_export(char *arg);
char	*return_key_export(char *arg);
char	*return_value_export(char *arg);
int		built_in_export(char **args, int argc, t_env **env);

// shlvl.c
char	*get_new_shlvl(char	*old);
int		change_shlvl_value(t_env *env);

#endif
