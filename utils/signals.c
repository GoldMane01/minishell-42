#include "../minishell.h"

void	ctrl_c_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGINT, ctrl_c_handler);
}

void	ctrl_quit_handler(int sig)
{
	signal(sig, SIG_IGN);
	printf("\n");
	printf("Quit (core dumped)\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGQUIT, ctrl_quit_handler);
}