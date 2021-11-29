#include "minishell.h"

void	init_g_sig(void)
{
	g_sig[0] = 0;
	g_sig[1] = 0;
	g_sig[2] = 0;
}

void	sig_int_handler(int sig)
{
	(void)sig;
	if (g_sig[0] == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig[1] = 1;
	}
	else if (g_sig[0] == 1)
	{
		write(1, "\n", 1);
		g_sig[1] = 130;
	}
	g_sig[2] = 1;
}

void	sig_quit_handler(int sig)
{
	if (g_sig[0] == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  ", 2);
		write(1, "\r", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_sig[0] == 1)
	{
		print_str_fd("Quit: ", ft_itoa(sig), "\n", 1);
		g_sig[1] = 131;
		g_sig[2] = 1;
	}
}
