/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:17:42 by yiken             #+#    #+#             */
/*   Updated: 2024/07/08 13:12:18 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_keychr(char c);
char	*ft_strdup(char *str);
int		key_match(char *var1, char *var2);
char	**getvar_ptr(char *var, char **arr);
int		arg_err(char *var, int err_print);
int		to_append(char *arg);
char	*ft_strjoin(char *s1, char *s2);
char	*dup_arg(char *str);
int		guests_len(char **args, char **envp, int *status);
int		envp_len(char **envp);

void	add_replace(char *finroot, char **envp, char **nenvp, int move_envp)
{
	static int	i;
	int			j;
	char		**ptr;

	if (move_envp)
	{
		j = 0;
		while (envp[j])
			nenvp[i++] = envp[j++];
		nenvp[i] = 0;
		i = 0;
		return ;
	}
	ptr = getvar_ptr(finroot, envp);
	if (ptr)
	{
		free(*ptr);
		*ptr = finroot;
	}
	else
		nenvp[i++] = finroot;
}

char	*mod_root(char *root, char *arg)
{
	char	*new_root;

	if (arg_err(arg, 0) || arg_err(arg, 0) == -1 || !key_match(root, arg))
		return (root);
	if (!to_append(arg))
	{
		new_root = ft_strdup(arg);
		return (free(root), new_root);
	}
	while (is_keychr(*arg))
		arg++;
	new_root = ft_strjoin(root, arg + 2);
	return (free(root), new_root);
}

char	*get_finroot(char **args, char **envp)
{
	char	*root;
	char	**var_ptr;
	int		i;

	i = 0;
	var_ptr = getvar_ptr(args[i], envp);
	if (var_ptr)
		root = ft_strdup(*var_ptr);
	else
		root = dup_arg(args[i++]);
	if (!root)
		return (write(2, "finroot fail\n", 13), NULL);
	while (args[i])
	{
		root = mod_root(root, args[i++]);
		if (!root)
			return (write(2, "finroot fail\n", 13), free(root), NULL);
	}
	return (root);
}

void	fill_replace(char **args, char **envp, char **nenvp, int *status)
{
	char	*finroot;
	char	*acc[200];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		acc[j] = 0;
		if ((arg_err(args[i], 0) || arg_err(args[i], 0) == -1
				|| getvar_ptr(args[i], acc)) && ++i)
			continue ;
		finroot = get_finroot(args + i, envp);
		if (!finroot)
			break ;
		add_replace(finroot, envp, nenvp, 0);
		if (j < 200)
			acc[j++] = finroot;
		i++;
	}
	if (args[i])
		*status = 1;
	if (nenvp)
		add_replace(finroot, envp, nenvp, 1);
}

int	ft_export(t_smplcmd *cmdlst, char ***envp)
{
	int		status;
	int		len;
	char	**nenvp;

	status = 0;
	nenvp = NULL;
	len = guests_len(cmdlst->argv + 1, *envp, &status);
	if (len == -1)
		return (1);
	if (len)
	{
		nenvp = malloc((envp_len(*envp) + len + 1) * sizeof(char *));
		if (!nenvp)
			return (1);
	}
	fill_replace(cmdlst->argv + 1, *envp, nenvp, &status);
	if (len)
	{
		free(*envp);
		*envp = nenvp;
	}
	return (status);
}
