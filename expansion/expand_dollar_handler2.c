#include "../includes/minishell.h"

char *expand_variable(char *s, int *i, t_env_exp *env, int next)
{
    int len;
    char *val;

    val = get_env_var(env, s, next, &len);
    *i = next + len - 1;
    return (val);
}

char *expand_invalid_dollars(int count, int *i)
{
    char *res;
    int start_i;

    start_i = *i;
    res = ft_calloc(1, 1);
    while (count--)
        res = exp_strjoin_free(res, "$");
    *i = start_i + count_dollars(res, 0) - 1; // move i to the last $ appended
    return (res);
}


char *handle_dollar(char *s, int *i, t_env_exp *env)
{
    int count;
    int next;
    char *result;

    count = count_dollars(s, *i);
    next = *i + count;
    if (s[next] == '\0' || !(is_var_char(s[next]) && !(s[next] >= '0' && s[next] <= '9')))
        result = expand_invalid_dollars(count, i);
    else
        result = expand_variable(s, i, env, next);
    return (result);
}

char *append_char(char *res, char c)
{
    char buf[2];
    
    buf[0] = c;
    buf[1] = '\0';
    return (exp_strjoin_free(res, buf));
}

char *simple_expand(char *s, t_env_exp *env)
{
    int i;
    char *result;
    char *tmp;
    i = 0;
    result  = ft_calloc(1, 1);
    while (s[i])
    {
        if (s[i] == '$')
        {
            tmp = handle_dollar(s, &i, env);
            result = exp_strjoin_free(result, tmp);
            free(tmp);
        }
        else
            result = append_char(result, s[i]);
        i++;
    }
    
    return (result);
}
