#include "tokenization.h"

char *extract_env_value(char *str)
{
    int i;
    int len;
    char *value;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    if(!str[i])
        return (NULL);
    len = ft_strlen(str) - (i + 1);
    value = malloc(sizeof(char) * (len + 1));
    if(!value)
        exit_error("minishell: malloc failed", 1);
    ft_strlcpy(value, str + i + 1, len + 1);
    return (value);
}

