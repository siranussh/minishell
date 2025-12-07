/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavgya@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:57:57 by anavagya          #+#    #+#             */
/*   Updated: 2025/12/07 14:57:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_new_shlvl(char	*old)
{
	int		level;
	char	*tmp;

	level = 0;
	if (!old || *old == '\0')
		return (ft_strdup("1"));
	level = atoi(old);
	if (level < 0)
		return (ft_strdup("1"));
	level++;
	if (level >= 1000)
	{
		tmp = ft_itoa(level);
		shlvl_error(tmp);
		free(tmp);
		return (ft_strdup("1"));
	}
	return (ft_itoa(level));
}

int	change_shlvl_value(t_env *env)
{
	char	*old_shlvl;
	char	*new_shlvl;

	old_shlvl = ft_strdup(get_env_values(env, "SHLVL"));
	new_shlvl = get_new_shlvl(old_shlvl);
	if (!change_env_value(env, "SHLVL", new_shlvl))
		ft_env_add_back(&env, ft_env_new("SHLVL", new_shlvl));
	free(new_shlvl);
	free(old_shlvl);
	return (1);
}
