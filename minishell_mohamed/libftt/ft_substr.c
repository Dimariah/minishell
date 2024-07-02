/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:47:32 by messkely          #+#    #+#             */
/*   Updated: 2024/06/08 11:35:42 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *str, int start, int end)
{
	int i;
	int substr_len;
	char *substr;

	i = 0;
	substr_len = end - start;
	substr = malloc((substr_len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (str[start] && start < end)
		substr[i++] = str[start++];
	substr[substr_len] = '\0';
	return (substr);
}
