#include "tokenization.h"

int find_closing_quote(int i, char *str, char c)
{
    while (str[i] && str[i] != c)
        i++;
    if(!str[i])
        return (-1);
    return (i);
}

int check_quotes_type(char *str)
{
    int i;
    int is_in_single;
    int is_in_double;

    i = 0;
    is_in_single = 0;
    is_in_double = 0;
    while (str[i])
    {
        if (str[i] == '"' && !is_in_single)
            is_in_double = !is_in_double;
        else if (str[i] == '\'' && !is_in_double)
            is_in_single = !is_in_single;
        if (str[i] == ' ' && (str[i + 1] == '"' || str[i + 1] == '\'') && str[i + 1] == str[i + 2] && str[i + 3] == ' ')
            return (-1);
        if ((str[i] == str[i + 1]) && ((str[i] == '"' && !is_in_single) || (str[i] == '\'' && !is_in_double)))
            return (-1);
        i++;
    }
    return (0);
}

static int check_quote_has_pair(char *str, int *i, char c)
{
    int quote_count;

    quote_count = 1;
    while(str[*i + 1] && str[*i + 1] != c)
        (*i)++;
    if(str[*i + 1] == c)
        quote_count++;
    (*i)++;
    return (quote_count);
}

int check_dquote(char *str, int is_double, int is_single, t_data *data)
{
    int i;

    i = 0;
    while (str[i])
    {
        if(str[i] == 34)
            is_double += check_quote_has_pair(str, &i, str[i]);
        if(str[i] == 39)
            is_single += check_quote_has_pair(str, &i, str[i]);
        if(is_double % 2 != 0 || is_single % 2 != 0)
        {
            data->flags->quote = 1;
            printf("dquote>\n");
            return (0);
        }
        i++;
    }
    return (1);
}

