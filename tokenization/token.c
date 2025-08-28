#include "tokenization.h"

static int split_tokens(char *str, char **token)
{
    int curr_pos;
    int start;
    int i;

    curr_pos = 0;
    start = 0;
    i = -1;
    while (str[++i])
    {
        if((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
            && str[i + 1] && str[i + 1] != ' ')
        start = i + 1;
        if (str[i] == '"' || str[i] == '\'')
            i = skip_quotes(i + 1, str, str[i]);
        if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13) && (str[i + 1] == ' ' || str[i + 1] == '\0'))
        {
            token[curr_pos] = ft_substr(str, start, i - start + 1);
            if (!token[curr_pos])
                exit_error("minishell: malloc failed", 1);
            curr_pos++;
        }
    }
    token[curr_pos] = NULL;
    return (i);
}

int main(void)
{
    char line[] = "echo \"hello world\" 'test 123' arg3";
    char *tokens[10];

    split_tokens(line, tokens);

    for (int i = 0; tokens[i]; i++)
    {
        printf("Token[%d]: '%s'\n", i, tokens[i]);
        free(tokens[i]);
    }

    return 0;
}