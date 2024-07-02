/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:06:25 by messkely          #+#    #+#             */
/*   Updated: 2024/06/09 12:06:44 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strcspn(const char *s, const char reject)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == reject)
			return (i);
		i++;
	}
	return (i);
}