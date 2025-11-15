#include "../includes/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>

int g_exit_code = 0;

void	disable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	enable_ctrl_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	child_handler(int sig)
{
	if (sig == SIGINT)
		g_exit_code = 130;
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		g_exit_code = 131;
	}
}

void	setup_signals(int parent_mode)
{
	if (parent_mode)
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
