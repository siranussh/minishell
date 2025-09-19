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

// int parse_line(t_data **data, char *line, char **tokens_by_pipe)
// {
//     (*data)->flags->quote = check_dquote(line, 2, 2, (*data));
//     if ((*data)->flags->quote == 0)
//     {
//         free(line);
//         return (1);
//     }
//     (*data)->flags->pipe = count_pipes(line);
//     if((*data)->flags->pipe = -1)
//     {
//         free(line);
//         return (1);
//     }
//     *tokens_by_pipe = split_pipes(line);
//     if (!(*tokens_by_pipe))
//     {
//         free(line);
//         return (1);
//     }
//     return (0);
// }
