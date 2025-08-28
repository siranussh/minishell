#include "tokenization.h"

int skip_quotes(int i, char *str, char c)
{
    while(str[i] && str[i] != c)
        i++;
    return (i);
}


int exit_error(char *str, int code)
{
    printf("%s\n", str);
    exit(code);
}