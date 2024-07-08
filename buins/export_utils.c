/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:43:13 by yiken             #+#    #+#             */
/*   Updated: 2024/07/04 17:43:59 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **envp, char *key, int key_len);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *str);
char	*trim_key(char *str);
int		is_keychr(char c);

int	env_found(char **envp, char *arg)
{
	char	*var_key;

	var_key = trim_key(arg);
	if (!var_key)
		return (write(2, "export: trim_key fail\n", 22), -1);
	return (find_var(envp, var_key,
			ft_strlen(var_key)) != NULL);
}

int	second_check(char *var, int i, int *eqsigns, int err_print)
{
	if (i == 0 || (var[i] != '=' && var[i] != '+')
		|| (var[i] == '+' && (*eqsigns || var[i + 1] != '=')))
	{
		if (err_print)
		{
			write(2, "export: `", 9);
			write(2, var, ft_strlen(var));
			write(2, "\': not a valid identifier\n", 26);
		}
		return (1);
	}
	if (var[i] == '=')
		(*eqsigns)++;
	return (0);
}

int	arg_err(char *var, int err_print)
{
	int	i;
	int	eqsigns;

	i = 0;
	eqsigns = 0;
	while ((i == 0 || var[i]) && !eqsigns)
	{
		if ((i == 0 && !var[i]) || (i == 0 && (var[i] <= '9' && var[i] >= '0'))
			|| (var[i] != '_' && (var[i] < '0' || var[i] > '9')
				&& (var[i] < 'a' || var[i] > 'z')
				&& (var[i] < 'A' || var[i] > 'Z')))
		{
			if (second_check(var, i, &eqsigns, err_print))
				return (1);
		}
		i++;
	}
	if (!eqsigns)
		return (-1);
	return (0);
}

int	last_occ(char **args)
{
	int		i;
	char	*arg;
	int		arg_keylen;
	int		key_len;

	arg = *args;
	arg_keylen = 0;
	while (is_keychr(arg[arg_keylen]))
		arg_keylen++;
	i = 1;
	while (args[i])
	{
		if (arg_err(args[i], 0) && ++i)
			continue ;
		key_len = 0;
		while (is_keychr(args[i][key_len]))
			key_len++;
		if (arg_keylen != key_len && ++i)
			continue ;
		if (!ft_strncmp(arg, args[i], key_len))
			return (0);
		i++;
	}
	return (1);
}

int	guests_len(char **args, char **envp, int *status)
{
	int	i;
	int	cntr;
	int	dup_status;
	int	err_status;

	i = 0;
	cntr = 0;
	while (args[i])
	{
		err_status = arg_err(args[i], 1);
		if (!err_status)
		{
			dup_status = env_found(envp, args[i]);
			if (dup_status == -1)
				return (-1);
			if (!dup_status && last_occ(args + i))
				cntr++;
		}
		else if (err_status != -1)
			*status = 1;
		i++;
	}
	return (cntr);
}
