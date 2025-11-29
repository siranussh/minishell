/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:43:32 by anavagya          #+#    #+#             */
/*   Updated: 2025/11/29 14:43:32 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_new_shlvl(char	*old)
{
	int	level;

	level = 0;
	if (!old || *old == '\0')
		return (ft_strdup("1"));
	level = atoi(old);
	if (level < 0)
		return (ft_strdup("1"));
	level++;
	if (level >= 1000)
	{
		print_error("minishell", "warning",
			"shell level too high, resetting to 1");
		return (ft_strdup("1"));
	}
	return (ft_itoa(level));
}

int	change_shlvl_value(t_env *env)
{
	char	*old_shlvl;
	char	*new_shlvl;

	old_shlvl = get_env_values(env, "SHLVL");
	new_shlvl = get_new_shlvl(old_shlvl);
	if (!change_env_value(env, "SHLVL", new_shlvl))
		ft_env_add_back(&env, ft_env_new("SHLVL", new_shlvl));
	free(new_shlvl);
	return (1);
}
