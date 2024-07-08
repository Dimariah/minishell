/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 12:16:49 by yiken             #+#    #+#             */
/*   Updated: 2024/07/08 13:13:43 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **envp, char *key, int key_len);
int		ft_strlen(char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		unset_kerror(char *key);
char	*unset_keygen(char *arg);
void	free_nenvp(char **nenvp, int k);
void	free_oldenvp(char **envp);

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
	char	*tmp_key;
	int		to_add;

	i = 0;
	k = 0;
	while (envp[i])
	{
		j = 0;
		to_add = 1;
		while (args[j])
		{
			tmp_key = unset_keygen(args[j++]);
			if (!tmp_key)
				return (free_nenvp(nenvp, k), 0);
			if (!ft_strncmp(envp[i], tmp_key, ft_strlen(tmp_key)))
				(free(envp[i]), to_add = 0);
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
		if (unset_kerror(cmdlst->argv[i]))
			status = 1;
		i++;
	}
	if (!fill_nenvp(envp, envp, cmdlst->argv + 1))
		return (write(2, "unset: tmp_key fail\n", 20), 1);
	return (status);
}
