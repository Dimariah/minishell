/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_reds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:44:48 by yiken             #+#    #+#             */
/*   Updated: 2024/07/22 00:08:37 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(char *s1, char *s2, size_t n);
int	ft_strlen(char *str);

void	here_doc(int *pipefd, int *std, char *lim, t_smplcmd *cmdlst)
{
	char	*str;
	char	*tmp;

	dup2(std[0], STDIN_FILENO);
	str = readline("> ");
	if (str && str[0] == '$' && !cmdlst->exp_herd)
		tmp = getenv(&str[1]);
	else
		tmp = getenv(str);
	while (str && ft_strncmp(str, lim, ft_strlen(lim) + 1))
	{
		if (tmp)
			write(pipefd[1], tmp, strlen(tmp));
		else
			write(pipefd[1], str, strlen(str));
		write(pipefd[1], "\n", 1);
		free(str);
		str = readline("> ");
		if (str && str[0] == '$' && !cmdlst->exp_herd)
			tmp = getenv(&str[1]);
		else
			tmp = getenv(str);
		printf("flag : %d\n", cmdlst->exp_herd);
	}
	free(str);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	inp_reds(char **reds, int *std, t_smplcmd *cmdlst)
{
	int	i;
	int	fdin;
	int	pipefd[2];

	i = 0;
	while (reds[i])
	{
		if (!ft_strncmp(reds[i], "<", 2))
		{
			fdin = open(reds[++i], O_RDONLY);
			if (fdin == -1)
				return (perror(reds[i]), 0);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		else if (!ft_strncmp(reds[i], "<<", 2))
		{
			if (pipe(pipefd) == -1)
				return (perror("pipe"), 0);
			here_doc(pipefd, std, reds[++i], cmdlst);
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
			fdout = open(reds[++i], O_TRUNC | O_CREAT | O_WRONLY, 0644);
			if (fdout == -1)
				return (perror(reds[i]), 0);
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		else if (!ft_strncmp(reds[i], ">>", 3))
		{
			fdout = open(reds[++i], O_APPEND | O_CREAT | O_WRONLY, 0644);
			if (fdout == -1)
				return (perror(reds[i]), 0);
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		i++;
	}
	return (1);
}

minishell> cat << '$'
I find It
> $USER
> $
flag : 1
$USER
minishell> cat << '"$"
I find It
> cat << '"^C
minishell> cat << "$"
I find It
> $USER
> $
flag : 1
$USER
minishell> 
