#include "tokenization.h"

int pipe_syntax_error(void)
{
    print_error("minishell", NULL, "syntax error near unexpected token '|'");
    global_error = 258;
    return -1;
}

int quote_error(void)
{
    print_error("minishell", NULL, "unexpected quote");
            global_error = 258;
            return -1;
}

int redir_error(void)
{
    print_error("minishell", NULL, "syntax error near unexpected token '>'");
            return (-1); 
}