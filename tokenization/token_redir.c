#include "../includes/minishell.h"

char **remove_token(char **tokens, int index)
{
    int     count;
    int     i;
    int     j;
    char    **result;

    if (!tokens)
        return (NULL);
    count = 0;
    while (tokens[count])
        count++;
    result = ft_calloc(sizeof(char *), count); // one less element
    if (!result)
        exit_error("malloc failed", 1);
    i = 0;
    j = 0;
    while (i < count)
    {
        if (i != index)
            result[j++] = ft_strdup(tokens[i]);
        free(tokens[i++]);
    }
    free(tokens);
    return (result);
}


char **add_token(char **tokens, char *new, int j)
{
    char **result;
    int i;
    int k;

    i = 0;
    k = 0;
    while (tokens[i])
        i++;
    result = ft_calloc(sizeof(char *), i + 1);
    if (!result)
        return (NULL);
    i = 0;
    while (tokens[k])
    {
        result[i] = ft_strdup(tokens[k]);
        free(tokens[k]);
        i++;
        k++;
        if(k == j)
            result[i++] = new;
    }
    free(tokens);
    return (result);
}

char **split_redirection_start(char **tokens, int j, char c)
{
    char *temp;
    int pos;

    pos = find_next_redir(tokens[j]);
    if (pos < 0)
        return (tokens);
    tokens = add_token(tokens, ft_substr(tokens[j], 0, pos), j + 1);
    temp = ft_strdup(ft_strchr(tokens[j], c));
    free(tokens[j]);
    tokens[j] = temp;
    return (split_redirection_tokens(tokens, j, c, 2));
}

char **split_redirection_tokens(char **tokens, int j, char c, int k)
{
    int i;
    i = 0;
    if (tokens[j][i] == '2' && tokens[j][i + 1] == '>')
        i++;
    while (tokens[j][i] == c)
        i++;
    if (!tokens[j][i])
        return (tokens);
    if (i == 0)
        return (split_redirection_start(tokens, j, c));
    tokens = add_token(tokens, ft_substr(tokens[j], 0, i), j + k++);
    tokens = add_token(tokens, ft_substr(tokens[j], i, find_next_redir(tokens[j]) - i), j + k++);
    i = find_next_redir(tokens[j]);
    if (tokens[j][i])
        tokens = add_token(tokens, ft_substr(tokens[j], i, ft_strlen(tokens[j]) - i), j + k++);
    tokens = remove_token(tokens, j);
    return (tokens);
}

void redir_tokens(t_cmd *cmd)
{
    int i = 0;

    if (!cmd || !cmd->tokens)
        return;

    while (cmd->tokens[i])
    {
        int type = redir_type(cmd->tokens[i]);

        if (type)
        {

            if (cmd->tokens[i + 1])
                cmd->tokens = remove_token(cmd->tokens, i + 1);
            cmd->tokens = remove_token(cmd->tokens, i);         
            continue;
        }
        i++;
    }
}





