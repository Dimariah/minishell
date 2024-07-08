/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 17:58:51 by yiken             #+#    #+#             */
/*   Updated: 2024/06/28 11:31:51 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_keychr(char c);
int		ft_strlen(char *str);
int		to_remove(char c);
char	*trim_key(char *str);
int		is_expandable(char *str);
char	*find_var(char **envp, char *key, int key_len);
void	expand_error(void);
void	code_len(int code, int *cntr);
void	cat_code(int code, char *new_str, int *j);

int	var_len(char **envp, char *str, int *cntr)
{
	char	*key;
	int		key_len;
	char	*var;

	key = trim_key(str);
	if (!key)
		return (-1);
	key_len = 0;
	while (str[key_len] && is_keychr(str[key_len]))
		key_len++;
	var = find_var(envp, key, key_len + 1);
	if (!var)
		return (0);
	*cntr += ft_strlen(var + (key_len + 1));
	return (0);
}

int	str_newsize(char **envp, char *str, int code)
{
	int	i;
	int	cntr;
	int	status;

	i = 0;
	cntr = 0;
	while (str[i])
	{
		status = is_expandable(str + i);
		if (status && str[i + 1] == '?' && ++i)
			code_len(code, &cntr);
		else if (status && to_remove(str[i + 1]))
			i++;
		else if (status && is_keychr(str[i + 1]))
		{
			if (var_len(envp, str + ++i, &cntr) == -1)
				return (-1);
			while (str[i + 1] && is_keychr(str[i + 1]))
				i++;
		}
		else
			cntr++;
		i++;
	}
	return (cntr);
}

int	cat_key_val(char **envp, char *str, char *new_str, int *j)
{
	char	*key;
	int		key_len;
	int		i;
	char	*var;

	key = trim_key(str);
	if (!key)
		return (-1);
	key_len = 0;
	while (str[key_len] && is_keychr(str[key_len]))
		key_len++;
	var = find_var(envp, key, key_len + 1);
	if (!var)
		return (0);
	i = key_len + 1;
	while (var[i])
		new_str[(*j)++] = var[i++];
	return (0);
}

int	fill_str(char **envp, char *str, char *new_str, int code)
{
	int	i;
	int	j;
	int	status;

	i = -1;
	j = 0;
	while (str[++i])
	{
		status = is_expandable(str + i);
		if (status && str[i + 1] == '?' && ++i)
			cat_code(code, new_str, &j);
		else if (status && to_remove(str[i + 1]))
			i++;
		else if (status && is_keychr(str[i + 1]))
		{
			if (cat_key_val(envp, str + ++i, new_str, &j) == -1)
				return (-1);
			while (str[i + 1] && is_keychr(str[i + 1]))
				i++;
		}
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (0);
}

char	*expd_line(char **envp, char *str, int code)
{
	char	*new_str;
	int		new_size;

	new_size = str_newsize(envp, str, code);
	if (new_size == -1)
		return (expand_error(), NULL);
	new_str = malloc(new_size + 1);
	if (!new_str)
		return (expand_error(), NULL);
	if (fill_str(envp, str, new_str, code) == -1)
	{
		free(new_str);
		return (expand_error(), NULL);
	}
	return (new_str);
}
