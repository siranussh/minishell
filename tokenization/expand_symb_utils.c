#include "tokenization.h"

int is_tilde_path(char *str)
{
    if (str && str[0] == '~' && (!str[1] || str[1] == '/'))
        return (1);
    return (0);
}

char *replace_tilde(char *str)
{
    char *home;
    char *result;
    size_t home_len;
    size_t rest_len;

    if(!str || str[0] != '~')
        return (str);
    home = getenv("HOME");
    if(!home)
        home = "";
    home_len = ft_strlen(home);
    rest_len = ft_strlen(str + 1);
    result = malloc(home_len + rest_len + 1);
    if(!result)
        exit_error("minishell: malloc failed", 1);
    ft_strlcpy(result, home, home_len + 1);
    ft_strlcpy(result + home_len, str + 1, rest_len + 1);
    free(str);
    return (result);
 }

 int is_invalid_dollar(char *str)
 {
    int i;

    i = -1;
    while (str[i] && str[i] != '$')
        i++;
    if (str[i] && str[i] == '$' && str[i + 1] && is_digit_or_special(str[i + 1]) == 1)
        return (0);
    else
        return (1);
 }

 int is_digit_or_special(int i)
{
    if(i == 42 || i == 64 || i == 92)
        return (1);
    else if(i < 48 || i > 57)
        return (0);
    return (1);
}

