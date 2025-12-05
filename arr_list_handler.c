/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <siranhakobyan13@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:27:57 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/05 18:04:35 by sihakoby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		exit_error("malloc failed", 1);
	res = ft_strjoin(tmp, s3);
	free(tmp);
	if (!res)
		exit_error("malloc failed", 1);
	return (res);
}

void	refresh_env_exp(t_data *data)
{
	if (data->env_exp)
		free_env_exp(&data->env_exp);
	data->env_exp = env_exp_from_list(data->env);
	if (!data->env_exp)
		exit_error("minishell: malloc failed", 1);
}

int	built_in_export_wrapper(char **args, int argc, t_data *data)
{
	int	res;

	free_env_exp(&data->env_exp);
	res = built_in_export(args, argc, &data->env);
	data->env_exp = env_exp_from_list(data->env);
	if (!data->env_exp)
		exit_error("minishell: malloc failed", 1);
	return (res);
}

int	built_in_unset_wrapper(char **args, t_data *data)
{
	int	res;

	res = built_in_unset(args, &data->env);
	refresh_env_exp(data);
	return (res);
}

char	*expand_var(t_data *data, char *key)
{
	char	*value;

	value = get_env_values(data->env, key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
