#include "tokenization.h"

char *extract_value_name(char *line)
{
    int i;
    int j;
    char *name;

    i = find_closing_quote(0, line, '$') + 1;
    j = 0;
    while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i + j] != 39 && is_special(line[i + j]) == 0)
        j++;
    name = ft_calloc(sizeof(char), j + 1);
    if (!name)
         exit_error("minishell: malloc failed", 1);
    j = 0;
    while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i + j] != 39 && is_special(line[i + j]) == 0)
    {
        name[j] = line[i + j];
        j++;
    }
   return (name);
}

char *extract_after_special(char *line, int i, t_cmd *cmd)
{
    int j;
    char *rest;

    cmd->flags->has_special = 1;
    j = i;
    while(line[i])
        i++;
    rest = malloc(sizeof(char) * (i - j + 1));
    if(!rest)
        exit_error("minishell malloc failed", 1);
    i = 0;
    while(line[j])
    {
        rest[i] = line[j];
        i++;
        j++;
    }
    rest[i] = '\0';
    return (rest);
}

