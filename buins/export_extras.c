/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:44:49 by yiken             #+#    #+#             */
/*   Updated: 2024/07/04 17:45:09 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_keychr(char c);
int		ft_strncmp(char *s1, char *s2, size_t n);

int	envp_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**getvar_ptr(char *var, char **arr)
{
	int	i;
	int	key_len;
	int	var_keylen;

	var_keylen = 0;
	while (is_keychr(var[var_keylen]))
		var_keylen++;
	i = 0;
	while (arr[i])
	{
		key_len = 0;
		while (is_keychr(arr[i][key_len]))
			key_len++;
		if (var_keylen != key_len && ++i)
			continue ;
		if (!ft_strncmp(var, arr[i], key_len))
			return (arr + i);
		i++;
	}
	return (NULL);
}

int	key_match(char *var1, char *var2)
{
	int	i;
	int	j;

	i = 0;
	while (is_keychr(var1[i]))
		i++;
	j = 0;
	while (is_keychr(var2[j]))
		j++;
	if (i != j)
		return (0);
	return (ft_strncmp(var1, var2, i) == 0);
}

int	to_append(char *arg)
{
	int	i;
	int	eqsigns;
	int	append;

	append = 0;
	i = 0;
	eqsigns = 0;
	while (arg[i])
	{
		if (!eqsigns && arg[i] == '+')
			append = 1;
		if (arg[i] == '=')
			eqsigns++;
		i++;
	}
	return (append);
}

char	*dup_arg(char *str)
{
	int		i;
	int		len;
	char	*new_str;
	int		eqsigns;

	len = 0;
	while (str[len])
		len++;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	len = 0;
	i = 0;
	eqsigns = 0;
	while (str[len])
	{
		if (str[len] == '=')
			eqsigns++;
		if (str[len] == '+' && !eqsigns && ++len)
			continue ;
		new_str[i++] = str[len++];
	}
	return (new_str[i] = '\0', new_str);
}
