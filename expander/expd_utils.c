/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:20:45 by yiken             #+#    #+#             */
/*   Updated: 2024/07/23 13:30:28 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n);
int	is_keychr(char c);

int	has_closure(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	check_hdoc(char *str, int *after_hdoc, int out_qts, int out_dq)
{
	if (out_qts && *str == '<' && str[1] == '<')
		*after_hdoc = 1;
	if (*after_hdoc && out_dq && (*str == ' ' && str[-1] != ' '))
	{
		if (str[-1] != '<' || (str[-1] == '<' && str[-2] != '<'))
			*after_hdoc = 0;
	}
}

int	is_expandable(char *str)
{
	static int	inside_dq;
	static int	inside_sq;
	static int	inside_uq;
	static int	after_hdoc;

	check_hdoc(str, &after_hdoc,
		(!inside_dq && !inside_sq && !inside_uq), !inside_dq);
	if (*str == '\'' && !inside_dq)
		inside_sq = !inside_sq;
	if (*str == '\"' && !inside_sq)
	{
		if (inside_dq || has_closure(str, *str))
		{
			inside_uq = 0;
			inside_dq = !inside_dq;
		}
		else
			inside_uq = 1;
	}
	if (*(str + 1) == '\0')
	{
		inside_sq = 0;
		inside_uq = 0;
		after_hdoc = 0;
	}
	return (*str == '$' && !inside_sq && !inside_uq && !after_hdoc);
}

char	*find_var(char **envp, char *key, int key_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len))
		{
			free(key);
			return (envp[i]);
		}
		i++;
	}
	free(key);
	return (NULL);
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
