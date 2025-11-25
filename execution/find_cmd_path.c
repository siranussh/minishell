/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/10/13 11:47:02 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/13 11:47:02 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*check_path(char *cmd, char **cmd_paths)
{
	char	*full_cmd;
	char	*tmp;
	int		i;

	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
			return (full_cmd);
		free(full_cmd);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	**cmd_paths;
	char	*path;
	char	*full_cmd;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_values(env, "PATH");
	if (!path)
	{
		print_error("minishell", cmd, "command not found");
		return (NULL);
	}
	cmd_paths = ft_split(path, ':');
	full_cmd = check_path(cmd, cmd_paths);
	ft_free(cmd_paths);
	return (full_cmd);
}
