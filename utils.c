#include "tokenization.h"

int skip_spaces(char *str, int i)
{
    while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
        i++;
    return (i);
}

char *str_tolower(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        str[i] = ft_tolower(str[i]);
        i++;
    }
    return (str);
}

char *unqoute_str(char *str)
{
    int i;
    int j;
    char *temp;
    int in_double;
    int single;

    i = -1;
    j = -1;
    in_double = 1;
    single = 1;
    temp = ft_calloc(1, ft_strlen(str) + 1);
    if (!temp)
        exit_error("minishell: malloc failed", 1);
    while (str[++i])
    {
        if (str[i] == 34 && single != -1)
            in_double = -in_double;
        else if (str[i] == 39 && in_double != -1)
            single = -single;
        else
            temp[++j] = str[i];
    }
    return (temp);
}

int check_spaces(char *str)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (str[++i])
    {
        if (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
        j++;
    }
    if (j == i || i == 0)
        return (-1);
    return (0);
}