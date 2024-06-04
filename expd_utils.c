/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:20:45 by yiken             #+#    #+#             */
/*   Updated: 2024/06/04 11:43:10 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libc.h"
#define NUM_AFTER 1
#define KEYCHR_AFTER 2

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && n-- > 1)
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	is_keychr(char c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'));
}

int	is_expandable(char *str, int index, int inside_sq) // //$USER
{
	if (str[index] != '$' || inside_sq 
		|| (index > 1 && str[index - 2] != '\\') 
		|| (index > 0 && str[index - 1] == '\\'))
		return (0);
	if (str[index + 1] >= '0' && str[index + 1] <= '9')
		return (NUM_AFTER);
	if (is_keychr(str[index + 1]))
		return (KEYCHR_AFTER);
	return (0);
}

char	*trim_key(char *str)
{
	char	*key;
	int		key_len;
	int		i;

	key_len = 0;
	while (str[key_len] && is_keychr(str[key_len]))
		key_len++;
	key = malloc(key_len + 2);
	if (!key)
	{
		write(2, "error while expanding\n", 22);
		exit(1);
	}
	i = 0;
	while (str[i] && is_keychr(str[i]))
	{
		key[i] = str[i];
		i++;
	}
	key[i++] = '=';
	key[i] = '\0';
	return (key);
}
