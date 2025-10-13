#include "tokenization.h"

int pipe_syntax_error(t_data *data)
{
    print_error("minishell", NULL, "syntax error near unexpected token '|'");
    data->exit_status = 258;
    return -1;
}

int quote_error(t_data *data)
{
    print_error("minishell", NULL, "unexpected quote");
    data->exit_status = 258;
            return -1;
}

int redir_error(void)
{
    print_error("minishell", NULL, "syntax error near unexpected token '>'");
            return (-1); 
}