#include "tokenization.h"

static void signal_handler(int sig)
{
    if(sig == SIGINT)
    {
        rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
        g_exit_code = 1;
    }
    else if(sig == SIGQUIT)
    {
        rl_on_new_line();
		rl_redisplay();
    }
    return ;
}

static void child_handler(int sig)
{
    if(sig == SIGINT)
        g_exit_code = 130;
    else if (sig == SIGQUIT)
    {
        write(1, "Quit: 3\n", 8);
        g_exit_code = 131;
    }
    return ;
}

void setup_signals(int parent_mode)
{
    if(parent_mode)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);
    }
    else
    {
        signal(SIGINT, child_handler);
        signal(SIGQUIT, child_handler);
    }
}