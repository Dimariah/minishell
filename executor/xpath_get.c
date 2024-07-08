/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpath_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:28:08 by yiken             #+#    #+#             */
/*   Updated: 2024/07/08 15:37:15 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(char *str, char c);
int		ft_strlen(char *str);
char	*find_var(char **envp, char *key, int key_len);
char	*ft_strdup(char *str);
int		exec_chbuin(t_smplcmd *cmdlst, char **envp, int *status);

char	*get_next_dir(char *path_var)
{
	static int	i;
	int			j;
	int			len;
	char		*dir;

	if (path_var[i] == ':')
		i++;
	len = 0;
	while (path_var[i + len] && path_var[i + len] != ':')
		len++;
	if (!len)
		return (NULL);
	dir = malloc(len + 1);
	if (!dir)
		return (write(2, "dir alloc fail\n", 15), NULL);
	j = 0;
	while (path_var[i] && path_var[i] != ':')
		dir[j++] = path_var[i++];
	dir[j] = '\0';
	return (dir);
}

char	*slash_join(char *dir, char *cmd)
{
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!path)
		return (write(2, "slash join fail\n", 16), NULL);
	while (dir[i])
		path[j++] = dir[i++];
	path[j++] = '/';
	i = 0;
	while (cmd[i])
		path[j++] = cmd[i++];
	path[j] = '\0';
	return (path);
}

char	*path_lookup(char *path_var, char *cmd, int *status)
{
	char	*dir;
	char	*to_test;

	dir = get_next_dir(path_var);
	while (dir)
	{
		to_test = slash_join(dir, cmd);
		free(dir);
		if (!to_test)
			return (write(2, "slash_join fail\n", 16), NULL);
		if (!access(to_test, X_OK) && *cmd)
			return (to_test);
		if (!access(to_test, F_OK) && access(to_test, X_OK))
		{
			*status = 126;
			return (perror(to_test), free(to_test), NULL);
		}
		free(to_test);
		dir = get_next_dir(path_var);
	}
	*status = 127;
	write(2, cmd, ft_strlen(cmd));
	return (write(2, ": command not found\n", 20), NULL);
}

char	*cmd_path(char *cmd, char **envp, int *status)
{
	char	*path_var;
	char	*key;
	char	*path;

	key = ft_strdup("PATH=");
	if (!key)
		return (write(2, "Key alloc fail\n", 15), NULL);
	path_var = find_var(envp, key, 5);
	if (!path_var)
	{
		*status = 127;
		if (access(cmd, X_OK))
			perror(cmd);
		return (NULL);
	}
	path = path_lookup(path_var + 5, cmd, status);
	return (path);
}

char	*get_path(char *xcutable, char **envp, int *status, t_smplcmd *cmdlst)
{
	char		*path;
	struct stat	filestat;

	if (!stat(xcutable, &filestat))
	{
		if (S_ISDIR(filestat.st_mode))
		{
			*status = 126;
			write(2, xcutable, ft_strlen(xcutable));
			return (write(2, ": is a directory\n", 17), NULL);
		}
	}
	path = xcutable;
	if (ft_strchr(xcutable, '/') && access(xcutable, X_OK))
	{
		*status = 127;
		if (!access(xcutable, F_OK))
			*status = 126;
		return (perror(xcutable), NULL);
	}
	else if (!ft_strchr(xcutable, '/') && exec_chbuin(cmdlst, envp, status))
		path = NULL;
	else if (!ft_strchr(xcutable, '/'))
		path = cmd_path(xcutable, envp, status);
	return (path);
}
