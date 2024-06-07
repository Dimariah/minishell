/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:20:45 by yiken             #+#    #+#             */
/*   Updated: 2024/06/07 20:41:57 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

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

int	is_num(char c)
{
	return (c >= '0' && c <= '9');
}

void	expand_error(void)
{
	write(2, "error while expanding\n", 22);
	exit(1);
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
		return (NULL);
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
