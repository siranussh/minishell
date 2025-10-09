/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:30:01 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/10 00:14:55 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/builtins.h"
#include "../includes/execution.h"

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	**cmd_paths;
	char	*path;
	char	*full_cmd;
	char	*tmp;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_values(env, "PATH");
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	cmd_paths = ft_split(path, ':');
	i = 0;
	while (cmd_paths[i])
	{
		tmp = ft_strjoin(cmd_paths[i], "/");
		full_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(cmd_paths);
			return (full_cmd);
		}
		free(full_cmd);
		i++;
	}
	ft_free(cmd_paths);
	return (NULL);
}
