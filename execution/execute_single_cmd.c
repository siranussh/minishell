/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:44:39 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/25 22:57:18 by anavagya         ###   ########.fr       */
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

int	execute_single_command(char **args, t_data *data)
{
	char	*path;
	char	**env_arr;

	if (!args || !*args)
		return (0);
	if (is_built_in(args))
		return (run_built_in(args_count(args), args, data));
	path = find_cmd_path(args[0], data->env);
	if (!path)
	{
		print_error("minishell", args[0], "command not found");
		return (127);
	}
	env_arr = env_to_array(data->env);
	execve(path, args, env_arr);
	print_error("minishell", args[0], "command not found");
	exit(127);
}
