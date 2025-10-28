/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:22:17 by anavagya          #+#    #+#             */
/*   Updated: 2025/10/28 13:55:25 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_built_in(char **args)
{
	char	**built_ins;
	int		i;

	built_ins = (char *[8]){"echo", "cd", "pwd", "env",
		"unset", "export", "exit", NULL};
	if (!args || !*args)
		return (0);
	i = 0;
	while (built_ins[i])
	{
		if (ft_strcmp(args[0], built_ins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	run_built_in(int argc, char **args, t_env *env)
{
	if (!args || !*args || !env)
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (built_in_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (built_in_cd(argc, args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (built_in_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (built_in_export(args, argc, &env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (built_in_unset(args, &env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (built_in_env(argc, args, env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (built_in_exit(argc, args));
	else
		return (1);
}
