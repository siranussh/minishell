#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int			g_exit_code = 0;

static void	signal_handler(int sig)
{
	g_exit_code = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler(int signo)
{
	(void)signo;
	g_exit_code = SIGINT;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_signals_parent_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

// void	setup_heredoc_signals(void)
// {
// 	signal(SIGINT, sigint_heredoc_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	restore_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
