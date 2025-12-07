/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:56:12 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:56:14 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	run_built_in(int argc, char **args, t_data *data)
{
	if (!args || !*args || !data || !data->env)
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (built_in_echo(args));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (built_in_cd(argc, args, data->env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (built_in_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (built_in_export_wrapper(args, argc, data));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (built_in_unset_wrapper(args, data));
	else if (ft_strcmp(args[0], "env") == 0)
		return (built_in_env(argc, args, data->env));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (built_in_exit(argc, args, data));
	else
		return (0);
}
