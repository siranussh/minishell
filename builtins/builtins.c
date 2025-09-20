/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 17:27:56 by anavagya          #+#    #+#             */
/*   Updated: 2025/09/06 14:02:30 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_built_in_type(char **args, char **envp)
{
	t_env	*env;

	env = env_parse(envp);
	if (args[0] == "echo")
		return (built_in_echo(args));
	else if (args[0] == "cd")
		return (built_in_cd(args));
	else if (args[0] == "pwd")
		return (built_in_pwd());
	else if (args[0] == "export")
		return (built_in_export(args));
	else if (args[0] == "unset")
		return (built_in_unset(args));
	else if (args[0] == "env")
		return (built_in_env(env));
	else if (args[0] == "exit")
		return (built_in_exit(args));
	else
		return (0);
}
