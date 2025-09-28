#include "tokenization.h"

int skip_double_quotes(char *str, int i, int j)
{
    i++;
    while (str[i] && str[i] != '"')
    {
        if(str[i] == '$' && i > j)
            return (i);
        i++;
    }
    return (-1);
}


int skip_single_quotes(char *str, int i)
{
    i++;
    while(str[i] && str[i] != '\'')
        i++;
    return i;
}

int find_next_char(char *str, char c, int j)
{
    int i;
    int pos;

    i = 0;
    while(str[i])
    {
        if(str[i] == '"')
        {
            pos = skip_double_quotes(str, i, j);
            if (pos != - 1)
                return pos;
            while(str[i] && str[i] != '"')
                i++;
        }
        else if (str[i] == '\'')
            i = skip_single_quotes(str, i);
        else if(str[i] == c && i > j)
        {
            if(c == '$' && str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\'' && str[i + 1] != '"')
                return (i);
            else if (c != '$')
                return (i);
        } 
        i++;
    }
    return (-1);
}

int is_digit_or_special(int i)
{
    if(i == 42 || i == 64 || i == 92)
        return (1);
    else if(i < 48 || i > 57)
        return (0);
    return (1);
}

int check_dollar_purpose(char *line)
{
    int i;
    int is_double;

    i = 0;
    is_double = 1;
    while(line[i])
    {
        if(line[i] == 39 && is_double == 1)
            i = find_closing_quote(i + 1,line, line[i]);
        if(line[i] == 34)
            is_double *= -1;
        if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
            return (1);
        i++;
    }
    return (0);
}