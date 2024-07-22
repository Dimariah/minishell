/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:47:34 by yiken             #+#    #+#             */
/*   Updated: 2024/07/21 23:58:03 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_beta_pid;
char	*get_path(char *xcutable, char **envp, int *status, t_smplcmd *cmdlst);
int		inp_reds(char **reds, int *std, t_smplcmd *cmdlst);
int		out_reds(char **reds);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		exec_pbuin(t_smplcmd *cmdlst, char ***envp, int *status);
void	restore_std(int *std);
void	lst_len_init(t_smplcmd *cmdlst);

int	pipe_dup(int *pipefd)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	return (1);
}

int	get_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	write(2, "process terminated abnormally\n", 30);
	return (1);
}

void	child_process(t_smplcmd *cmdlst, int *pipefd, char **envp)
{
	char	*path;
	int		status;

	if (cmdlst->next)
		close(pipefd[0]);
	if (!(cmdlst->argv[0]))
		exit(0);
	status = 1;
	path = get_path(cmdlst->argv[0], envp, &status, cmdlst);
	if (!path)
		exit(status);
	execve(path, cmdlst->argv, envp);
	perror("execve");
	if (ft_strncmp(cmdlst->argv[0], path, 1))
		free(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(1);
}

int	exec_cmd(t_smplcmd *cmdlst, int *std, char **envp)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (cmdlst->next && pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	if (!inp_reds(cmdlst->reds, std, cmdlst) || (cmdlst->next && !pipe_dup(pipefd))
		|| (cmdlst->list_len > 1 && !out_reds(cmdlst->reds)))
	{
		dup2(pipefd[0], STDIN_FILENO);
		return (close(pipefd[1]), close(pipefd[0]), 1);
	}
	pid = fork();
	if (pid == -1)
	{
		dup2(pipefd[0], STDIN_FILENO);
		return (close(pipefd[0]), close(pipefd[1]), perror("fork"), 1);
	}
	else if (pid == 0)
		child_process(cmdlst, pipefd, envp);
	wait(&status);
	dup2(std[1], STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	return (close(pipefd[0]), WEXITSTATUS(status));
}

int	exec_cmds(t_smplcmd *cmdlst, char ***envp)
{
	int	status;
	int	std[2];

	lst_len_init(cmdlst);
	status = 0;
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	if (!cmdlst->next && exec_pbuin(cmdlst, envp, &status))
		return (restore_std(std), 1);
	g_beta_pid = fork();
	if (g_beta_pid == -1)
		return (perror("fork"), 1);
	if (g_beta_pid == 0)
	{
		ch_handle_signals();
		while (cmdlst)
		{
			status = exec_cmd(cmdlst, std, *envp);
			cmdlst = cmdlst->next;
		}
		restore_std(std);
		exit(status);
	}
	wait(&status);
	return (g_beta_pid = -1, restore_std(std), exit_status(get_status(status)));
}
