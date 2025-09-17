#include "tokenization.h"

// static int split_tokens(char *str, char **token)
// {
//     int curr_pos;
//     int start;
//     int i;

//     curr_pos = 0;
//     start = 0;
//     i = -1;
//     while (str[++i])
//     {
//         if ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)) && str[i + 1] && str[i + 1] != ' ')
//             start = i + 1;
//         if (str[i] == '"' || str[i] == '\'')
//             i = find_closing_quote(i + 1, str, str[i]);
//         if (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13) && (str[i + 1] == ' ' || str[i + 1] == '\0'))
//         {
//             token[curr_pos] = ft_substr(str, start, i - start + 1);
//             if (!token[curr_pos])
//                 exit_error("minishell: malloc failed", 1);
//             curr_pos++;
//         }
//     }
//     token[curr_pos] = NULL;
//     return (i);
// }

// static char **get_token_arr(t_data *data, char *str, t_cmd *cmd)
// {
//     char **token;
//     char *temp;

//     temp = str;
//     if (check_quotes_type(temp) == -1)
//         temp = skip_empty_quotes(ft_strtrim(temp, " "), cmd);
//     token = malloc(sizeof(char *) * (cmd ->num_tokens + 1));
//     if (!token)
//         exit_error("minishell: malloc failed", 1);
//     data->total_chars += split_tokens(str, token);
//     if (check_quotes_type(str) == -1)
//         free(temp);
//     return (token);
// }

// static char *extract_command(t_data *data, char *line)
// {
//     int i;
//     int start;
//     char *str;
    
//     i = 0;
//     while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
//         i++;
//     start = i;
//     while (line[i] && line[i]!= 32
//     && !(line[i] >= 9 && line[i] <= 13)
//     && !is_other_op(line[i]))
//     {
//         if(line[i] == '"' || line[i] == '\'')
//             i = find_closing_quote(i + 1, line, line[i]);
//         i++;
//     }
//     if (i == start || is_other_op(line[i]))
//         str = NULL;
//     else
//         str = ft_substr(line, start, i - start);
//         data->total_chars += i;
//         return (str);
// }

// static t_cmd *build_cmd(t_data *data, char *line)
// {
//     t_cmd *temp;

//     temp = ft_calloc(sizeof(t_cmd), 1);
//     if (!temp)
//         exit_error("minishell: malloc failed", 1);
//     temp->cmd = extract_command(data, line + data->total_chars);
//     temp->num_tokens = count_tokens(line + data->total_chars);
//     temp->next = NULL;
//     temp->env = data->env;
//     if (temp->num_tokens == 0)
//         return (temp);
//     temp->tokens = get_token_arr(data, line + data->total_chars, temp);
//     return (temp);
// }



