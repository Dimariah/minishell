/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:14:27 by messkely          #+#    #+#             */
/*   Updated: 2024/06/27 17:37:51 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *dst, const char *src)
{
	int	dl;
	int	sl;
	int	j;

	dl = ft_strlen(dst);
	sl = ft_strlen(src);
	j = 0;
	while (j < sl)
	{
		dst[dl] = src[j];
		dl++;
		j++;
	}
	dst[dl] = '\0';
	return (dst);
}

static void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (s1);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	free(s1);
	return (result);
}
