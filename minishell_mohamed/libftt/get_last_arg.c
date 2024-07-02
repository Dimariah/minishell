/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_last_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:08:32 by messkely          #+#    #+#             */
/*   Updated: 2024/06/09 12:08:45 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_last_arg(const char *s, int del)
{
	if (!s)
		return (0);
	while(*s)
	{
		if (del)
			return ((char *)s);
		s++;
	}
	return (NULL);
}