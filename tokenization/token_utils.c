#include "tokenization.h"

int count_tokens(char *str)
{
    int i;
    int result;

    i = -1;
    result = 0;
    while (str[++i])
    {
        if((str[i] != 32 && str[i] != 34 && str[i] != 39)
        && (str[i + 1] == 32 || str[i + 1] == '\0' || str[i + 1] == 34 || str[i + 1] == 39))
            result ++;
        if(str[i] == 34 || str[i] == 39)
        {
            result++;
            i = find_closing_quote(i + 1, str, str[i]);
        }
    }
    return (result);
}


