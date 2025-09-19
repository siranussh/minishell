#include "tokenization.h"

int is_other_op(char c)
{
    if(c == '>' || c == '<')
        return (c);
    return (0);
}

int count_pipes(char *str)
{
    int i;
    int result;

    if(!str)
        return (0);
    i = 0;
    result = 0;
    while(str[i])
    {
        if(str[i] == 34 || str[i] == 39)
            i = find_closing_quote(i + 1, str, str[i]);
        if(i == -1)
        {
            return (quote_error());
        }
        if((str[i] == '|' && (str[i + 1] == '|' || str[i + 1] == '\0')) || str[0] == '|')
        {
            return (pipe_syntax_error());
        }
        if(str[i] == '|')
            result ++;
        i++;
    }
    return (result);
}
