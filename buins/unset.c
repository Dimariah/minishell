/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:16:49 by yiken             #+#    #+#             */
/*   Updated: 2024/07/10 16:10:51 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **envp, char *key, int key_len);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		unset_kerror(char *key, int err_print);
int		key_match(char *var1, char *var2);

int	unset_isdup(char **vars_found, char *tmp_var)
{
	int	i;

	i = 0;
	while (vars_found[i])
	{
		if (!ft_strncmp(vars_found[i], tmp_var, ft_strlen(tmp_var) + 1))
			return (1);
		i++;
	}
	return (0);
}

static int	fill_nenvp(char **envp, char **nenvp, char **args)
{
	int		i;
	int		j;
	int		k;
	int		to_add;

	i = 0;
	k = 0;
	while (envp[i])
	{
		j = 0;
		to_add = 1;
		while (args[j])
		{
			if (!unset_kerror(args[j], 0) && key_match(envp[i], args[j]))
			{
				(free(envp[i]), to_add = 0);
				break ;
			}
			j++;
		}
		if (to_add)
			nenvp[k++] = envp[i];
		i++;
	}
	return (nenvp[k] = 0, 1);
}

int	unset(t_smplcmd *cmdlst, char **envp)
{
	int		status;
	int		i;

	status = 0;
	i = 1;
	while (cmdlst->argv[i])
	{
		if (unset_kerror(cmdlst->argv[i], 1))
			status = 1;
		i++;
	}
	fill_nenvp(envp, envp, cmdlst->argv + 1);
	return (status);
}
