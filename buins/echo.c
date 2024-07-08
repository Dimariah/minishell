/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:35:40 by yiken             #+#    #+#             */
/*   Updated: 2024/07/07 14:28:26 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	echo(char **args)
{
	int	i;
	int	is_option;

	i = 1;
	is_option = 0;
	while (args[i] && (ft_strcmp(args[i], "-n") == 0))
	{
		if (ft_strcmp(args[i], "-n") == 0)
			is_option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (is_option == 0)
		printf("\n");
	return (0);
}
