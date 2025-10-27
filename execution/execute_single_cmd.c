/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:39 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 11:44:39 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "../includes/execution.h"

int	args_count(char **args)
{
	int	count;

	if (!args || !*args)
		return (-1);
	count = 0;
	while (args[count])
		count++;
	return (count);
}

char	**env_to_array(t_env *env)
{
	int		i;
	int		size;
	char	*tmp;
	char	**env_arr;

	size = ft_env_size(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->key, "=");
			env_arr[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			i++;
		}
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	execute_single_command(char **args, t_env *env)
{
	char	*path;
	int		pid;
	char	**env_arr;

	if (!args || !*args)
		return (0);
	if (is_built_in(args))
		return (run_built_in(args_count(args), args, env));
	path = find_cmd_path(args[0], env);
	if (!path)
		return (127);
	pid = fork();
	if (pid == 0)
	{
		env_arr = env_to_array(env);
		execve(path, args, env_arr);
		perror("execve");
		exit(1);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		free(path);
	}
	else
		perror("fork");
	return (0);
}
