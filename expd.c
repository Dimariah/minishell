/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:58:51 by yiken             #+#    #+#             */
/*   Updated: 2024/06/04 17:20:52 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <readline/readline.h>
#define NUM_AFTER 1
#define KEYCHR_AFTER 2

int		is_keychr(char c);
int		is_expandable(char *str, int index, int inside_sq);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *str);
char	*trim_key(char *str);

int	var_len(char **envp, char *str)
{
	int		i;
	char	*key;
	int		key_len;

	key = trim_key(str);
	key_len = 0;
	while (str[key_len] && is_keychr(str[key_len]))
		key_len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len + 1))
		{
			free(key);
			return (ft_strlen(envp[i] + (key_len + 1)));
		}
		i++;
	}
	free(key);
	return (0);
}

int	handle_sq(char c, int *inside_sq)
{
	static int	inside_dq;

	if (c == '\0')
		return (0);
	if (c == '\"' && inside_dq == 0 && *inside_sq == 0)
		inside_dq = 1;
	else if (c == '\"' && inside_dq == 1)
		inside_dq = 0;
	if (c == '\'' && *inside_sq == 0 && inside_dq == 0)
		*inside_sq = 1;
	else if (c == '\'' && *inside_sq == 1)
		*inside_sq = 0;
	return (1);
}

int	str_newsize(char **envp, char *str)
{
	int		i;
	int		cntr;
	int		inside_sq;

	i = 0;
	cntr = 0;
	inside_sq = 0;
	while (handle_sq(str[i], &inside_sq))
	{
		if (is_expandable(str, i, inside_sq) == NUM_AFTER)
			i++;
		else if (is_expandable(str, i, inside_sq) == KEYCHR_AFTER)
		{
			cntr += var_len(envp, str + ++i);
			while (str[i + 1] && is_keychr(str[i + 1]))
				i++;
		}
		else
			cntr++;
		i++;
	}
	return (cntr);
}

int	cat_key_val(char **envp, char *str, char *new_str, int j)
{
	char	*key;
	int		key_len;
	int		i;
	int		k;

	key = trim_key(str);
	key_len = 0;
	while (str[key_len] && is_keychr(str[key_len]))
		key_len++;
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, key_len + 1))
		{
			free(key);
			k = key_len + 1;
			while (envp[i][k])
				new_str[j++] = envp[i][k++];
			return (j);
		}
		i++;
	}
	free(key);
	return (j);
}

char	*expd_str(char **envp, char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		inside_sq;

	new_str = malloc(str_newsize(envp, str) + 1);
	i = 0;
	j = 0;
	inside_sq = 0;
	while (handle_sq(str[i], &inside_sq))
	{
		if (is_expandable(str, i, inside_sq) == NUM_AFTER)
			i++;
		else if (is_expandable(str, i, inside_sq) == KEYCHR_AFTER)
		{
			j = cat_key_val(envp, str + ++i, new_str, j);
			while (str[i + 1] && is_keychr(str[i + 1]))
				i++;
		}
		else
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
