/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sihakoby <sihakoby@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:27:57 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/03 18:22:37 by sihakoby         ###   ########.fr       */
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

// t_env_exp *env_exp_from_list(t_env *env_list)
// {
//     t_env_exp *exp;
//     t_env *tmp;
//     int count;

//     if (!env_list)
//         return (NULL);
//     tmp = env_list;
//     count = 0;
//     while (tmp)
//     {
//         count++;
//         tmp = tmp->next;
//     }
//     exp = ft_calloc(1, sizeof(t_env_exp));
//     if (!exp)
//         exit_error("malloc failed", 1);

//     exp->env = ft_calloc(count + 1, sizeof(char *));
//     if (!exp->env)
//         exit_error("malloc failed", 1);

//     tmp = env_list;
//     for (int i = 0; i < count; i++)
//     {
//         if (tmp->value)
//             exp->env[i] = ft_strjoin_three(tmp->key, "=", tmp->value);
//         else
//             exp->env[i] = ft_strdup(tmp->key);

//         if (!exp->env[i])
//             exit_error("malloc failed", 1);
//         tmp = tmp->next;
//     }
//     exp->env[count] = NULL;
//     exp->num_env = count;
//     exp->path = NULL;

//     return (exp);
// }

// void free_env_exp(t_env_exp **env_exp_ptr)
// {
// 	t_env_exp	*e;
// 	int			i;

// 	if (!env_exp_ptr || !*env_exp_ptr)
// 		return ;
// 	e = *env_exp_ptr;
// 	if (e->env)
// 	{
// 		for (i = 0; i < e->num_env; ++i)
// 		{
// 			if (e->env[i])
// 			{
// 				free(e->env[i]);
// 				e->env[i] = NULL;
// 			}
// 		}
// 		free(e->env);
// 		e->env = NULL;
// 	}
// 	if (e->path)
// 	{
// 		free(e->path);
// 		e->path = NULL;
// 	}
// 	free(e);
// 	*env_exp_ptr = NULL;
// }

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
