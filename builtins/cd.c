/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/02 17:11:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

char	*get_env_values(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) != 0)
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
		if (ft_strcmp(env->key, key) == 0)
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
		return (free(old_pwd), 0);
	}
	printf("Changed directory to: %s\n", path);//////
	change_env_value(env, "OLDPWD", old_pwd);
	cwd = getcwd(NULL, 0);
	// printf("cwd = %s\n", cwd);
	// printf("old_pwd = %s\n", old_pwd);
	change_env_value(env, "PWD", cwd);
	free(old_pwd);
	free(cwd);
	return (1);
}

int	built_in_cd(int argc, char **args, t_env *env)
{
	char	*old_pwd;
	char	*home;
	int		status;

	if (argc > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	home = get_env_values(env, "HOME");
	if (argc == 1)
	{
		if (!home)
		{
			printf("minishell: cd: HOME not set\n");
			return (free(old_pwd), 1);
		}
		if (cd_helper(home, old_pwd, env))
			status = 0;
		else
			status = 1;
	}
	if (argc == 2)
	{
		if (cd_helper(args[1], old_pwd, env))
			status = 0;
		else
			status = 1; 
	}
	return (status);
}
