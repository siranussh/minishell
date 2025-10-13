#include "tokenization.h"

char *replace_exit_code(char *str,int i, t_data *data)
{
    char *before;
    char *after;
    char *err_str;
    char *tmp;
    char *result;

    err_str = ft_itoa(data->exit_status);
    if (!err_str)
        return (NULL);
    before = ft_substr(str, 0, i);
    after = ft_strdup(str + i + 2);
    if(!before || !after)
        return (free(before), free(after), free(err_str), NULL);
    tmp = ft_strjoin(before, err_str);
    free(before);
    free(err_str);
    if (!tmp)
        return (free(after), NULL);
    result = ft_strjoin(tmp, after);
    free(tmp);
    free(after);
    free(str);
    return (result);
}

char *replace_all_exit_code(char *str, t_data *data)
{
    int i;
    int j;
    i = find_closing_quote(0, str, '?') - 1;
    while(str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
            str = replace_exit_code(str, i, data);
        j = i;
        i = find_closing_quote(0, str, '$');
        if (j == i)
            break;
    }
    return (str);
}


