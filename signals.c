#include "../includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int			g_exit_code = 0;

// static void	signal_handler(int sig)
// {
// 	g_exit_code = sig;
// 	write(1, "\n", 1);
// 	// rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	sigint_handler(int signo)
// {
// 	(void)signo;
// 	g_exit_code = SIGINT;
// 	// rl_replace_line("", 0);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void	setup_signals(void)
// {
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	setup_signals_parent_exec(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// // void	setup_heredoc_signals(void)
// // {
// // 	signal(SIGINT, sigint_heredoc_handler);
// // 	signal(SIGQUIT, SIG_IGN);
// // }

// void	restore_signals(void)
// {
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

static void	in_ctrl(int num)
{
	set_status(FAILURE);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}

void	nonin_ctrl(int num)
{
	write(STDOUT_FILENO, "\n", 1);
	(void)num;
}

static void	b_slash(int num)
{
	(void)num;
}

static void	h_ctrl(int num)
{
	(void)num;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	if (get_status() == 222)
		write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	set_status(222);
}

void    sigint_interactive(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_parent(int sig)
{
	(void)sig;
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);  // stops readline
}

void	setup_signals(int num)
{
	if (num == INTERACTIVE)
	{
		signal(SIGINT, sigint_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == NINTERACTIVE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (num == HEREDOC)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
