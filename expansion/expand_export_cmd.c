#include "../includes/minishell.h"

static int is_space(char c)
{
    return (c == ' ' || (c >= 9 && c <= 13));
}

char **split_var_value(char *str)
{
    char **tokens;
    int i = 0, start = 0, token_count = 0;
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i])
        {
            token_count++;
            while (str[i] && !is_space(str[i]))
            {
                if (str[i] == '\'' || str[i] == '\"')
                {
                    char quote = str[i++];
                    while (str[i] && str[i] != quote)
                        i++;
                    if (str[i])
                        i++;
                }
                else
                    i++;
            }
        }
    }
    tokens = malloc(sizeof(char *) * (token_count + 1));
    if (!tokens)
        return NULL;
    i = 0;
    token_count = 0;
    while (str[i])
    {
        while (str[i] && is_space(str[i]))
            i++;
        if (str[i])
        {
            start = i;
            while (str[i] && !is_space(str[i]))
            {
                if (str[i] == '\'' || str[i] == '\"')
                {
                    char quote = str[i++];
                    while (str[i] && str[i] != quote)
                        i++;
                    if (str[i])
                        i++;
                }
                else
                    i++;
            }
            tokens[token_count++] = strndup(str + start, i - start);
        }
    }
    tokens[token_count] = NULL;
    return tokens;
}
char **expand_var_for_execution(char *expanded_value)
{
    if (!expanded_value)
        return NULL;
    if (strchr(expanded_value, ' '))
        return split_var_value(expanded_value);

    char **args = malloc(sizeof(char *) * 2);
    if (!args)
        return NULL;
    args[0] = strdup(expanded_value);
    args[1] = NULL;
    return args;
}



