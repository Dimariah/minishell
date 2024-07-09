/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:42:50 by messkely          #+#    #+#             */
/*   Updated: 2024/07/09 15:45:51 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

static char	*ft_strcpy(char *dst, const char *src, int pos, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[pos + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	int		len;
	char	*ptr;

	start = 0;
	end = 0;
	if (*s1 == 0)
		return (s1);
	while (s1[start] && ft_strchr(set, s1[start]) != 0)
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, s1[end]) != 0)
		end--;
	len = end - start + 1;
	ptr = (char *)malloc(len + 1);
	if (!ptr)
		return (0);
	ptr = ft_strcpy(ptr, s1, start, len);
	return (ptr);
}

int	lst_len(t_smplcmd *cmdlst)
{
	int	i;

	i = 0;
	while (cmdlst)
	{
		i++;
		cmdlst = cmdlst->next;
	}
	return (i);
}
