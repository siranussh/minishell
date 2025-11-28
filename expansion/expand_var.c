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
char	*handle_dollar(char *str, int *i, t_env_exp *env)
{
	int		dcount;
	int		vlen;
	char	*tmp;
	char	*val;

	if (str[*i + 1] == '?')
		return (expand_exit_status(str, i));
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
char	*expand_exit_status(char *str, int *i)
{
	char	*val;
	char	*res;

	val = ft_itoa(g_exit_code);
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

