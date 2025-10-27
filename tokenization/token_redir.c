#include "tokenization.h"

char **remove_token(char **tokens, int index)
{
    char **result;
    int count;
    int res_idx;

    count = 0;
    while (tokens[count])
        count++;

    result = ft_calloc(sizeof(char *), count);
    if (!result)
        exit_error("malloc failed", 1);

    res_idx = count - 2;
    while (--count >= 0)
    {
        if (count != index)
        {
            result[res_idx] = ft_strdup(tokens[count]);
            res_idx--;
        }
        free(tokens[count]);
    }
    free(tokens);
    return result;
}

char **add_token(char **tokens, char *new, int j)
{
    char **result;
    int i;
    int k;

    i = 0;
    while (tokens[i])
        i++;
    result = ft_calloc(sizeof(char *), i + 1);
    if (!result)
        return (NULL);
    i = 0;
    k = 0;
    while (tokens[k])
    {
        result[i++] = ft_strdup(tokens[k]);
        free(tokens[k]);
        if (k++ == j)
            result[i++] = new;
    }
    if (k == j)
        result[i++] = new;
    result[i] = NULL;
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
    int i;
    int idx;
    int count;

    i = 0;
    while (cmd->tokens && cmd->tokens[i])
    {
        idx = is_redir(cmd->tokens + i);
        if (idx == -1)
            break;
        i += idx;
        if (!cmd->tokens[i])
            break;
        cmd->tokens = split_redirection_tokens(cmd->tokens, i,
                    redir_smb(redir_type(cmd->tokens[i])), 1);
        if (!redir_type(cmd->tokens[i]))
            i++;
        if (cmd->tokens[i + 1] && redir_type(cmd->tokens[i + 1]))
            cmd->tokens = split_redirection_tokens(cmd->tokens, i + 1,
                        redir_smb(redir_type(cmd->tokens[i + 1])), 1);
        count = 0;
        while (count++ < 2 && cmd->tokens[i])
            cmd->tokens = remove_token(cmd->tokens, i);
    }
}



