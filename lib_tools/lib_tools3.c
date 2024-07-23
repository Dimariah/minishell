/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:00:41 by messkely          #+#    #+#             */
/*   Updated: 2024/07/23 16:21:39 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *s, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = ft_strlen(s);
	if (n > len)
		n = len;
	new_str = (char *)malloc(n + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[n] = '\0';
	return (new_str);
}

int	ft_arglen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exit_status(int exit_status)
{
	static int	value;

	if (exit_status != -500)
		value = exit_status;
	return (value);
}

void	flags_todef(int *inside_sq, int *inside_uq, int *after_hdoc)
{
	*inside_sq = 0;
	*inside_uq = 0;
	*after_hdoc = 0;
}
