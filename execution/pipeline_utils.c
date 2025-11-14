/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:22:05 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/14 22:11:08 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

void	dup2_and_close(int fd1, int fd2)
{
	if (fd1 != fd2)
	{
		dup2(fd1, fd2);
		close(fd1);
	}
}

int	wait_for_children(t_pipe *p)
{
	int		i;
	int		status;
	int		exit_code;

	exit_code = 0;
	i = 0;
	while (i < p->cmds_count)
	{
		waitpid(p->pids[i], &status, 0);
		if (i == (p->cmds_count - 1) && WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	free(p->pids);
	return (exit_code);
}

char	**cpy_str_arr(char **str)
{
	int		i;
	int		size;
	char	**str_cpy;

	if (!str || !*str)
		return (NULL);
	i = 0;
	size = args_count(str);
	str_cpy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!str_cpy)
		return (NULL);
	while (str[i])
	{
		str_cpy[i] = ft_strdup(str[i]);
		if (!str_cpy[i])
		{
			while (i-- < 0)
				free(str_cpy[i]);
			return (free(str_cpy), NULL);
		}
		i++;
	}
	str_cpy[i] = NULL;
	return (str_cpy);
}
