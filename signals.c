/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:20:27 by messkely          #+#    #+#             */
/*   Updated: 2024/07/13 11:44:37 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_beta_pid;

void	ft_handle_sigint(int sig)
{
	if (g_beta_pid > 0)
		kill(g_beta_pid, SIGTERM);
	if (g_beta_pid == -1 || g_beta_pid > 0)
		write(2, "\n", 1);
	if (g_beta_pid == -1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(1);
	}
	g_beta_pid = -1;
	(void)sig;
}

void	ft_handle_sigquit(int sig)
{
	if (g_beta_pid >= 0)
	{
		kill(g_beta_pid, SIGABRT);
		write(2, "Quit: 3\n", 8);
	}
	g_beta_pid = -1;
	rl_replace_line("", 0);
	(void)sig;
}

void	ft_handle_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, ft_handle_sigquit);
}

void	ch_handle_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
