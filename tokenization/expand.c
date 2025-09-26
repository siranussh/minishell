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

char *expand_dollar(char *new_line, char *line, char *var, int c)
{
    int i;
    int j;
    int k;

    i = -1;
    j = -1;
    k = find_next_char(line, '$', -1);
    if((size_t)k == ft_strlen(line))
        return (line);
    while(++i < k)
        new_line[i] = line[i];
    while(var[++j])
        new_line[i + j] = var[j];
    while(line[i + c])
    {
        new_line[i + j] = line[i + c];
        i++;
    }
    new_line[i + j] = '\0';
    return (new_line);
}

char *expand_line(char *line, char*var)
{
    int i;
    int j;
    char *new_line;

    i = find_next_char(line, '$', -1);
    if (i < 0)
        return (line);
    j = 0;
    while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i + j] != 39)
        j++;
    new_line = malloc(ft_strlen(line) - j + ft_strlen(var) + 1);
    if (!new_line)
        exit_error("minishell: malloc failed", 1);
    new_line = expand_dollar(new_line, line, var, j);
    free(line);
    free(var);
    return (new_line);
}