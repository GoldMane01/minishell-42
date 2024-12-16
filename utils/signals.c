/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmunoz- <crmunoz-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:36:17 by crmunoz-          #+#    #+#             */
/*   Updated: 2024/12/16 19:45:50 by crmunoz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
