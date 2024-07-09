/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:08:37 by yiken             #+#    #+#             */
/*   Updated: 2024/07/09 17:30:43 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(char **envp, char *key, int key_len);
int		ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	**getvar_ptr(char *var, char **arr);
int		envp_len(char **envp);

char	*npath_expd(char c, char **envp)
{
	char	*key;
	int		key_len;
	char	*npath;

	if (c == '~')
	{
		key = ft_strdup("HOME=");
		key_len = 5;
	}
	if (c == '-')
	{
		key = ft_strdup("OLDPWD=");
		key_len = 7;
	}
	if (!key)
		return (write(2, "cd: key malloc fail\n", 20), NULL);
	npath = find_var(envp, key, key_len);
	if (!npath)
		return (NULL);
	return (npath + key_len);
}

char	*get_npath(char **args, char **envp)
{
	char	*npath;

	npath = args[1];
	if (!args[1])
	{
		npath = npath_expd('~', envp);
		if (!npath)
			return (write(2, "cd: HOME not set\n", 17), NULL);
	}
	else if (args[1][0] == '-' && !args[1][1])
	{
		npath = npath_expd('-', envp);
		if (!npath)
			return (write(2, "cd: OLDPWD not set\n", 19), NULL);
	}
	return (npath);
}

int	oldpwd_up(char *cwd, char ***envp)
{
	char	**oldpwd_ptr;
	char	**nenvp;
	char	*cwd_dup;
	int		i;

	oldpwd_ptr = getvar_ptr("OLDPWD=", *envp);
	nenvp = NULL;
	cwd_dup = ft_strjoin("OLDPWD=", cwd);
	if (!cwd_dup)
		return (write(2, "cd: OLDPWD update fail\n", 23), 0);
	if (oldpwd_ptr)
		return (free(*oldpwd_ptr), *oldpwd_ptr = cwd_dup, 1);
	nenvp = malloc((envp_len(*envp) + 2) * sizeof(char *));
	if (!nenvp)
		return (write(2, "cd: OLDPWD add fail\n", 20), 0);
	i = 0;
	while ((*envp)[i])
	{
		nenvp[i] = (*envp)[i];
		i++;
	}
	nenvp[i++] = cwd_dup;
	return (free(*envp), nenvp[i] = NULL, *envp = nenvp, 1);
}

int	ch_cd(t_smplcmd *cmdlst, char **envp)
{
	char	*npath;

	npath = get_npath(cmdlst->argv, envp);
	if (!npath)
		return (1);
	if (chdir(npath) != 0 && npath[0])
		return (write(2, "cd: ", 4), perror(npath), 1);
	if (cmdlst->argv[1] && cmdlst->argv[1][0] == '-')
	{
		write(1, npath, ft_strlen(npath));
		write(1, "\n", 1);
	}
	return (0);
}

int	cd(t_smplcmd *cmdlst, char ***envp)
{
	char	*npath;
	char	cwd[1024];
	int		chdir_st;

	if (!getcwd(cwd, sizeof(cwd)))
		return (write(2, "cd: ", 4), perror("getwcwd"), 1);
	npath = get_npath(cmdlst->argv, *envp);
	if (!npath)
		return (1);
	chdir_st = chdir(npath);
	if ((!chdir_st || !(*npath))
		&& cmdlst->argv[1] && cmdlst->argv[1][0] == '-')
	{
		write(1, npath, ft_strlen(npath));
		write(1, "\n", 1);
	}
	if (!chdir_st)
	{
		if (!oldpwd_up(cwd, envp))
			return (1);
	}
	else if (npath[0])
		return (write(2, "cd: ", 4), perror(npath), 1);
	return (0);
}
