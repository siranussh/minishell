/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_path_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:08:03 by sihakoby          #+#    #+#             */
/*   Updated: 2025/10/11 21:35:49 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "pipex_bonus.h"

static char	*get_env_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (envp[i] != NULL && envp[i][0] != '\0')
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = ft_substr(path, 5, ft_strlen(path));
			break ;
		}
		i++;
	}
	return (path);
}

static char	**add_slash_to_the_path_end(char **paths)
{
	int		i;
	char	*temp_path;

	i = 0;
	temp_path = NULL;
	while (paths[i])
	{
		temp_path = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free_str_or_arr_bonus(temp_path, NULL);
		i++;
	}
	return (paths);
}

static char	**split_env_path(char **envp)
{
	char	*env_path_str;
	char	**paths;

	env_path_str = get_env_path(envp);
	if (!env_path_str || *env_path_str == '\0')
	{
		error_msg_bonus("command not found", "", "", 1);
		return (NULL);
	}
	paths = ft_split(env_path_str, ':');
	free_str_or_arr_bonus(env_path_str, NULL);
	if (!paths)
		return (NULL);
	paths = add_slash_to_the_path_end(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*get_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	cmd_path = NULL;
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_str_or_arr_bonus(NULL, paths);
			error_bonus(error_msg_bonus("unexpected error", "", "", 1),
				NULL);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free_str_or_arr_bonus(cmd_path, NULL);
		i++;
	}
	return (NULL);
}

char	*get_cmd_bonus(char *cmd, t_data *data)
{
	char	**env_paths;
	char	*cmd_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	env_paths = split_env_path(data->envp);
	if (!env_paths)
	{
		error_msg_bonus("command not found", ": ", data->av[data->child + 2], 1);
		return (NULL);
	}
	cmd_path = get_cmd_path(cmd, env_paths);
	if (!cmd_path)
		error_msg_bonus("command not found", ": ",
			data->av[data->child + 2], 1);
	free_str_or_arr_bonus(NULL, env_paths);
	return (cmd_path);
}
