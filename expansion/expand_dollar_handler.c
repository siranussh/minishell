#include "../includes/minishell.h"

int  count_dollars(char *s, int i)
{
    int count;

    count = 0;
    while(s[i + count] == '$')
        count++;
    return (count);
}

int is_var_char(char c)
{
    return ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
             c == '_');
}

int get_var_len(char *s, int i)
{
    int len;

    len = 0;
    while (s[i + len] && is_var_char(s[i + len]))
        len++;
    return (len);
}

char *get_env_var(t_env_exp *env, char *s, int i, int *len)
{
    char *name;
    char *val;
    *len = get_var_len(s, i);
    int j;

    j = 0;
    name = ft_substr(s, i, *len);
    val = NULL;
    while (j < env->num_env)
    {
        if (ft_strncmp(env->env[j], name, ft_strlen(name)) == 0
    && env->env[j][ft_strlen(name)] == '=')
    {
        val = extract_env_value(env->env[j]);
        break;
    }
    j++;
    }
    free(name);
    if (!val)
        val = ft_strdup("");
    return (val);
}