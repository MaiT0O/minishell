/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebansse <ebansse@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:15:29 by cguinot           #+#    #+#             */
/*   Updated: 2025/06/23 15:07:12 by ebansse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	handle_sigint_interactive(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_command(int sig)
{
	(void)sig;
	g_signal_received = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
}

void	setup_signals(int mode)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sa_quit.sa_flags = SA_RESTART;
	if (mode == 0)
	{
		sa_int.sa_handler = handle_sigint_interactive;
		sa_quit.sa_handler = SIG_IGN;
	}
	else if (mode == 1)
	{
		sa_int.sa_handler = handle_sigint_command;
		sa_quit.sa_handler = SIG_IGN;
	}
	else if (mode == 2)
	{
		sa_int.sa_handler = SIG_DFL;
		sa_quit.sa_handler = SIG_DFL;
	}
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	check_and_handle_signals(t_shell *shell)
{
	if (g_signal_received == SIGINT)
	{
		shell->last_status = 130;
		g_signal_received = 0;
	}
}
