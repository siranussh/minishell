/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:04:32 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/06 22:24:35 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

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

int	check_access(char *args)
{
	if (ft_strchr(args, '/'))
	{
		if (access(args, F_OK) == -1)
		{
			print_error("minishell", args, "No such file or directory");
			return (127);
		}
		if (access(args, X_OK) == -1)
		{
			print_error("minishell", args, "Permission denied");
			return (126);
		}
		if (is_directory(args))
		{
			print_error("minishell", args, "Is a directory");
			return (126);
		}
	}
	return (0);
}

int	execute_single_command(char **args, t_data *data)
{
	char	*path;
	char	**env_arr;
	int		access_value;

	if (!args || !*args)
		return (0);
	if (is_built_in(args))
		return (run_built_in(args_count(args), args, data));
	access_value = check_access(args[0]);
	if (access_value == 0)
	{
		path = find_cmd_path(args[0], data->env);
		if (!path)
			return (print_error("minishell", args[0],
					"command not found"), 127);
	}
	else
		return (access_value);
	env_arr = env_to_array(data->env);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(path, args, env_arr);
	free_data(data);
	print_error("minishell", args[0], "command not found");
	return (127);
}
