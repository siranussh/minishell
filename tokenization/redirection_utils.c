#include "tokenization.h"

int is_other_op(char c)
{
    if(c == '>' || c == '<')
        return (c);
    return (0);
}

