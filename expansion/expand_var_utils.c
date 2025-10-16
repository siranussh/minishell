#include "tokenization.h"

char *extract_value_name(char *line)
{
    int i;
    int j;
    char *name;
    i = find_closing_quote(0, line, '$') + 1;
    j = 0;
    while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && is_special(line[i + j]) == 0)
        j++;

    name = ft_calloc(sizeof(char), j + 1);
    if (!name)
        exit_error("minishell: malloc failed", 1);
    j = 0;
    while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"'
		&& line[i + j] != 39 && is_special(line[i + j]) == 0)
    {
        name[j] = line[i + j];
        j++;
    }
    return name;
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

char *replace_val(t_cmd *cmd, char *line, char **rest_line, t_data *data)
{
    char *name;
    int i;

    if(ft_strnstr(line, "$?", ft_strlen(line)) != 0)
        return (replace_all_exit_code(line,data));
    name = extract_value_name(line);
    if (!name)
    return (NULL);
if(!name[0])
    return (ft_strdup(ft_strchr(line, '$') + 1));
    i = find_next_char(line, '$', -1);
    while (line[++i] && line[i] != ' ')
    {
        if((is_special(line[i]) == -1
            && line[i] != '$') || (line[i] == '$'
            && i == find_next_char(line, '$', find_next_char(line, '$', -1) + 1)))
        {
            *rest_line = extract_after_special(line, i, cmd);
            break;
        }
    }
    return (cmp_value_name(cmd, line, name));
}

char *replace_all_val(t_cmd *cmd, char *str, char *rest_line, t_data *data)
{
    char *temp;

    if (!str)
        return (NULL);

    if (is_invalid_dollar(str) == 0)
        str = delete_invalid_dollar(str, -1, -1);

    if (!str || check_dollar_purpose(str) == 0)
        return (str);

    cmd->flags->has_special = 0;
    str = replace_val(cmd, str, &rest_line, data);
    if (!str)
        return (NULL);

    if (cmd->flags->has_special == 1)
    {
        temp = exp_strjoin(str, rest_line, 0, 0);
        free(str);
        str = temp;
        free(rest_line);
        rest_line = NULL;
        cmd->flags->has_special = 0;
    }

    if (check_dollar_purpose(str) == 1)
        str = replace_all_val(cmd, str, NULL, data);

    if (rest_line)
        free(rest_line);

    return (str);
}
