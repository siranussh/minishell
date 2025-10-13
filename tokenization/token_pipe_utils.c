#include "tokenization.h"

int count_pipes(char *str, t_data *data)
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
            return (quote_error(data));
        if((str[i] == '|' && (str[i + 1] == '|' || str[i + 1] == '\0')) || str[0] == '|')
        {
            return (pipe_syntax_error(data));
        }
        if(str[i] == '|')
            result ++;
        i++;
    }
    return (result);
}

char **split_cmds_by_pipe(char *str, char **result)
{
    int i;
    int start;
    int pos;

    i = -1;
    start = 0;
    pos = 0;
    while (str[++i])
    {
        if(str[i] == 34 || str[i] == 39)
            i = find_closing_quote(i + 1, str, str[i]);
        if((str[i + 1] == '|' || str[i + 1] == '\0') && str[i] != '|')
        {
            result[pos] = ft_substr(str, start, i - start + 1);
            if (!result[pos])
                exit_error("minishell: malloc failed", 1);
            pos++;
        }
        if(str[i] == '|' && (str[i + 1] != '|' || str[i + 1] != '\0'))
            start = i + 1;
    }
    result[pos] = NULL;
    return (result);
}

int check_pipe_seg(char *str)
{
    int i;

    i = 0;

    while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
        i++;
    if (!str[i])
    {
        print_error("minishell", NULL, "syntax error near unexpected token '|'");
        return -1;
    }
    return 0;
}


char **split_pipes(char *str, t_data *data)
{
    char **result;
    int i;

    i = -1;
    result = ft_calloc(sizeof(char *), (count_pipes(str, data) + 2));
    if (!result)
        exit_error("minishell: malloc failed", 1);
    result = split_cmds_by_pipe(str, result);
    while (result[++i])
    {
        if (check_pipe_seg(result[i]) == -1 || check_redir(result, i) == -1)
        {
            data->exit_status= 258;
            while (i >= 0)
                free(result[i--]);
            free(result);
            return (NULL);
        }
    }
    return (result);
}

void handle_pipelines(t_data *data, t_cmd **cmd, char **lines)
{
    int i;
    t_cmd *temp;
    t_cmd *last;

    i = 1;
    while(lines[i])
    {
        temp = build_cmd(data, lines[i]);
        expand(&temp, data);

        last = last_cmd(cmd);
        if (last)
            last->next = temp;

        i++;
    }
}