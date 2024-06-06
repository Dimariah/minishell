/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:58:51 by yiken             #+#    #+#             */
/*   Updated: 2024/06/06 17:15:43 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>

int		is_keychr(char c);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *str);
char	*trim_key(char *str);
int		is_num(char c);

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

int	is_expandable(char c)
{
	static int	inside_dq;
	static int	inside_sq;
	static int	inside_bs;
	int			status;

	if (c == '\\')
		inside_bs = !inside_bs;
	if (c == '\'' && !inside_bs && !inside_dq)
		inside_sq = !inside_sq;
	if (c == '\"' && !inside_bs && !inside_sq)
		inside_dq = !inside_dq;
	status = (c == '$' && !inside_sq && !inside_bs);
	if (c != '\\')
		inside_bs = 0;
	return (status);
}

int	str_newsize(char **envp, char *str)
{
	int		i;
	int		cntr;
	int		inside_sq;
	int		status;

	i = 0;
	cntr = 0;
	inside_sq = 0;
	while (str[i])
	{
		status = is_expandable(str[i]);
		if (status && is_num(str[i + 1]))
			i++;
		else if (status && is_keychr(str[i + 1]))
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

char	*expd_line(char **envp, char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		status;

	new_str = malloc(str_newsize(envp, str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		status = is_expandable(str[i]);
		if (status && is_num(str[i + 1]))
			i++;
		else if (status && is_keychr(str[i + 1]))
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
