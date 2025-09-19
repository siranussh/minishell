#include "tokenization.h"

int exit_error(char *str, int code)
{
    printf("%s\n", str);
    exit(code);
}


void print_error(char *name, char *file, char *err)
{
    ft_putstr_fd(name, 2);
    ft_putstr_fd(": ", 2);
    if(file)
    {
        ft_putstr_fd(file, 2);
        ft_putstr_fd(": ", 2);
    }
    if (err)
        ft_putendl_fd(err, 2);
    else
        ft_putstr_fd("\n", 2);
}

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