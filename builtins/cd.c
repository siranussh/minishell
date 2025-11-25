/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:26 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/25 23:09:56 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	cd_helper(char *path, char *old_pwd, t_env *env)
{
	char	*cwd;
	t_env	*tmp;

	if (chdir(path) == -1)
	{
		print_error("minishell: cd", path, "No such file or directory");
		return (free(old_pwd), 0);
	}
	if (!get_env_values(env, "OLDPWD"))
	{
		tmp = ft_env_new("OLDPWD", ft_strdup(old_pwd));
		ft_env_add_back(&env, tmp);
	}
	change_env_value(env, "OLDPWD", old_pwd);
	cwd = getcwd(NULL, 0);
	change_env_value(env, "PWD", cwd);
	free(old_pwd);
	free(cwd);
	return (1);
}

void	cd_minus(char *old_pwd, int *status, t_env *env)
{
	char	*old;
	char 	*old_copy;

	old = get_env_values(env, "OLDPWD");
	if (!old)
	{
		print_error("minishell", "cd", "OLDPWD not set");
		free(old_pwd);
		*status = 1;
		return ;
	}
	old_copy = ft_strdup(old);
	if (cd_helper(old, old_pwd, env))
		*status = 0;
	else
		*status = 1;
	printf("%s\n", old_copy);
	free(old_copy);	
}

void	cd_with_argument(char **args, char *old_pwd, int *status, t_env *env)
{
	if (ft_strcmp(args[1], "-") == 0)
		cd_minus(old_pwd, status, env);
	else
	{
		if (cd_helper(args[1], old_pwd, env))
			*status = 0;
		else
			*status = 1; 
	}
}

int	built_in_cd(int argc, char **args, t_env *env)
{
	char	*old_pwd;
	char	*home;
	int		status;

	status = 0;
	if (argc > 2)
		return (print_error("minishell", "cd", "too many arguments"), 1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (argc == 1)
	{
		home = get_env_values(env, "HOME");
		if (!home)
			return (print_error("minishell", "cd", "HOME not set"),
				free(old_pwd), 1);
		if (cd_helper(home, old_pwd, env))
			status = 0;
		else
			status = 1;
	}
	else if (argc == 2)
		cd_with_argument(args, old_pwd, &status, env);
	return (status);
}
