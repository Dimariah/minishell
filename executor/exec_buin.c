/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:26:52 by yiken             #+#    #+#             */
/*   Updated: 2024/07/24 17:42:11 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n);
int	cd(t_smplcmd *cmdlst, char ***envp);
int	unset(t_smplcmd *cmdlst, char **envp);
int	ch_unset(t_smplcmd *cmdlst, int x_status);
int	inp_reds(char **reds, int *std);
int	out_reds(char **reds);
int	ft_export(t_smplcmd *cmdlst, char ***envp);
int	arg_err(char *var, int err_print);
int	ch_cd(t_smplcmd *cmdlst, char **envp, int x_status);
int	echo(char **args);
int	pwd(void);
int	env(char **envp);
int	ft_exit(t_smplcmd *cmdlst, char **args, char **envp);
int	ch_exit(char **args);

int	ch_export(t_smplcmd *cmdlst, int x_status)
{
	int	i;
	int	status;

	if (cmdlst->list_len == 1)
		return (x_status);
	i = 1;
	status = 0;
	while (cmdlst->argv[i])
	{
		if (arg_err(cmdlst->argv[i], 1) == 1)
			status = 1;
		i++;
	}
	return (status);
}

int	exec_pbuin(t_smplcmd *cmdlst, char ***envp)
{
	char	*xcutable;

	xcutable = cmdlst->argv[0];
	if (!ft_strncmp(xcutable, "cd", 3))
		return (cd(cmdlst, envp));
	if (!ft_strncmp(xcutable, "unset", 6))
		return (unset(cmdlst, *envp));
	if (!ft_strncmp(xcutable, "export", 7))
		return (ft_export(cmdlst, envp));
	if (!ft_strncmp(xcutable, "exit", 5))
		return (ft_exit(cmdlst, cmdlst->argv, *envp));
	return (0);
}

int	exec_chbuin(t_smplcmd *cmdlst, char **envp, int *status)
{
	char	*xcutable;
	int		x_status;

	x_status = *status;
	xcutable = cmdlst->argv[0];
	if (!ft_strncmp(xcutable, "cd", 3))
		return (*status = ch_cd(cmdlst, envp, x_status), 1);
	if (!ft_strncmp(xcutable, "unset", 6))
		return (*status = ch_unset(cmdlst, x_status), 1);
	if (!ft_strncmp(xcutable, "export", 7))
		return (*status = ch_export(cmdlst, x_status), 1);
	if (!ft_strncmp(xcutable, "echo", 5))
		return (*status = echo(cmdlst->argv), 1);
	if (!ft_strncmp(xcutable, "pwd", 4))
		return (*status = pwd(), 1);
	if (!ft_strncmp(xcutable, "env", 4))
		return (*status = env(envp), 1);
	if (!ft_strncmp(xcutable, "exit", 5))
		return (*status = ch_exit(cmdlst->argv), 1);
	return (0);
}
