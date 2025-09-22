/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 12:51:25 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/22 12:51:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_env_values(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) != 0)
			env = env->next;
		else
			return (env->value);
	}
	return (NULL);
}

int	change_env_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->name, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	cd_helper(char *path, char *old_pwd, t_env *env)
{
	char	*cwd;

	if (chdir(path) == -1)
	{
		perror("minishell");
		return (0);
	}
	change_env_value(env, "OLDPWD", old_pwd);
	cwd = getcwd(NULL, 0);
	change_env_value(env, "PWD", cwd);
	free(old_pwd);
	free(cwd);
	return (1);
}

int	built_in_cd(int argc, char **args, t_env *env)
{
	char	*old_pwd;
	char	*home;

	(void)args;
	if (argc > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (0);
	}
	old_pwd = getcwd(NULL, 0);
	home = get_env_values(env, "HOME");
	if (!home)
		return (0);
	if (argc == 1)
	{
		cd_helper(home, old_pwd, env);
	}
	if (argc == 2)
	{
		cd_helper(args[1], old_pwd, env);
	}
	return (1);
}
