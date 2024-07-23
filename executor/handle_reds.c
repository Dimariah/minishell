/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_reds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:44:48 by yiken             #+#    #+#             */
/*   Updated: 2024/07/23 13:48:56 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strlen(char *str);
char	*expd_line(char **envp, char *str, int code);
int		exit_status(int exit_status);
void	restore_std(int *std);
char	*rm_escape_char(char *s);

int	here_doc(int *std, char *lim, t_smplcmd *cmdlst, char **envp)
{
	char	*str;
	int		pipefd[2];
	int		out_save;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	out_save = dup(STDOUT_FILENO);
	restore_std(std);
	str = readline("> ");
	while (str && ft_strncmp(str, lim, ft_strlen(lim) + 1))
	{
		if (cmdlst->exp_herd)
		{
			str = expd_line(envp, str, exit_status(-500));
			if (!str)
				return (0);
		}
		write(pipefd[1], str, ft_strlen(str));
		(write(pipefd[1], "\n", 1), free(str));
		str = readline("> ");
	}
	(free(str), free(lim), dup2(out_save, STDOUT_FILENO));
	(close(out_save), dup2(pipefd[0], STDIN_FILENO));
	return (close(pipefd[1]), close(pipefd[0]), 1);
}

int	open_file(char *file, int mode)
{
	char	*unq_file;
	int		fd;

	if (!file)
		return (-1);
	unq_file = rm_escape_char(file);
	if (mode == 1)
		fd = open(unq_file, O_RDONLY);
	if (mode == 2)
		fd = open(unq_file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	if (mode == 3)
		fd = open(unq_file, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		perror(unq_file);
	free(unq_file);
	return (fd);
}

char	*unq_lim(char *lim, t_smplcmd *cmdlst)
{
	cmdlst->exp_herd = 1;
	if (*lim == '\"' || *lim == '\'')
		cmdlst->exp_herd = 0;
	return (rm_escape_char(lim));
}

int	inp_reds(char **reds, int *std, char **envp, t_smplcmd *cmdlst)
{
	int		i;
	int		fdin;
	char	*lim;

	i = 0;
	while (reds[i])
	{
		if (!ft_strncmp(reds[i], "<", 2))
		{
			fdin = open_file(reds[++i], 1);
			if (fdin == -1)
				return (0);
			(dup2(fdin, STDIN_FILENO), close(fdin));
		}
		else if (!ft_strncmp(reds[i], "<<", 2))
		{
			lim = unq_lim(reds[++i], cmdlst);
			if (!lim || !here_doc(std, lim, cmdlst, envp))
				return (0);
		}
		i++;
	}
	return (1);
}

int	out_reds(char **reds)
{
	int	i;
	int	fdout;

	i = 0;
	while (reds[i])
	{
		if (!ft_strncmp(reds[i], ">", 2))
		{
			fdout = open_file(reds[++i], 2);
			if (fdout == -1)
				return (0);
			(dup2(fdout, STDOUT_FILENO), close(fdout));
		}
		else if (!ft_strncmp(reds[i], ">>", 3))
		{
			fdout = open_file(reds[++i], 3);
			if (fdout == -1)
				return (0);
			(dup2(fdout, STDOUT_FILENO), close(fdout));
		}
		i++;
	}
	return (1);
}
