/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 03:53:33 by messkely          #+#    #+#             */
/*   Updated: 2024/07/01 06:22:18 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_echo(char **av)
{
	int i;
	int is_option;

	i = 1;
	is_option = 0;
	while (av[i] && (ft_strcmp(av[i], "-n") == 0))
	{
		if (ft_strcmp(av[i], "-n") == 0)
			is_option = 1;
		i++;
	}
	while (av[i])
	{
		ft_putstr_fd(av[i], 1);
		if (av[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (is_option == 0)
		write(1, "\n", 1);
	return (0);
}

int main()
{
	// char *line[] = 	{"echo", "-e", "-e", "-n", "-e", "hello", "world", NULL};
	char *line[] = 	{"echo", "-n", "-n", "hello", "world", NULL};
	return (ft_echo(line));
}