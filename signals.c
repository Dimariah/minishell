/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 08:20:27 by messkely          #+#    #+#             */
/*   Updated: 2024/07/25 15:09:44 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pid_holder(int pid);

void	ft_handle_sigint(int sig)
{
	write(2, "\n", 1);
	if (pid_holder(-500) == -1)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(1);
	}
	(void)sig;
}

void	ft_handle_sigquit(int sig)
{
	if (pid_holder(-500) > 0)
		write(2, "Quit: 3\n", 8);
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
