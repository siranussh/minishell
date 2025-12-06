/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anavagya <anavagya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 14:11:06 by sihakoby          #+#    #+#             */
/*   Updated: 2025/12/06 21:29:57 by anavagya         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

int	handle_quotes(char c, int *in_single, int *in_double)
{
	if (c == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
		return (1);
	}
	if (c == '\"' && !(*in_single))
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

char	*handle_dollar(char *str, int *i, t_env_exp *env, t_data *data)
{
	int		dcount;
	int		vlen;
	char	*tmp;
	char	*val;

	if (str[*i + 1] == '?')
		return (expand_exit_status(str, i, data));
	dcount = count_dollars(str, *i);
	vlen = get_var_len(str, *i + dcount);
	if (vlen == 0)
	{
		*i += dcount;
		return (str);
	}
	tmp = ft_substr(str, *i + dcount, vlen);
	val = get_env_var(env, tmp, 0, &vlen);
	free(tmp);
	str = replace_with_value(str, i, val, dcount + vlen);
	free(val);
	return (str);
}

char	*expand_exit_status(char *str, int *i, t_data *data)
{
	char	*val;
	char	*res;

	val = ft_itoa(data->exit_code);
	res = build_new_line(str, val, *i, 2);
	free(val);
	free(str);
	*i += ft_strlen(res) - *i;
	return (res);
}

char	*replace_with_value(char *str, int *i, char *val, int skip_len)
{
	char	*new_str;

	new_str = build_new_line(str, val, *i, skip_len);
	free(str);
	*i += ft_strlen(val);
	return (new_str);
}

char	*build_new_line(char *line, char *insert, int pos, int remove_len)
{
	char	*new_line;
	int		new_len;
	int		j;
	int		k;
	int		rest;

	new_len = ft_strlen(line) - remove_len + ft_strlen(insert) + 1;
	new_line = malloc(new_len);
	if (!new_line)
		return (NULL);
	j = 0;
	k = 0;
	while (k < pos)
		new_line[j++] = line[k++];
	k = 0;
	while (insert[k])
		new_line[j++] = insert[k++];
	rest = pos + remove_len;
	while (line[rest])
		new_line[j++] = line[rest++];
	new_line[j] = '\0';
	return (new_line);
}
