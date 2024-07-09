/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:17:55 by yiken             #+#    #+#             */
/*   Updated: 2024/07/09 15:46:31 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *str);

char	*ft_strdup(char *str)
{
	char	*clone;
	int		i;

	clone = malloc(ft_strlen(str) + 1);
	if (!clone)
		return (NULL);
	i = 0;
	while (str[i])
	{
		clone[i] = str[i];
		i++;
	}
	clone[i] = '\0';
	return (clone);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	return (str[i] = '\0', str);
}

int	ft_isdigit(int c)
{
	if ((c >= 48 && c <= 57))
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	restore_std(int *std)
{
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
}
