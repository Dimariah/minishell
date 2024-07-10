/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:10:38 by yiken             #+#    #+#             */
/*   Updated: 2024/07/10 16:51:44 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_isdigit(int c);
int		envp_len(char **envp);
int		ft_isspace(char c);
int		ft_strlen(char *str);

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i])
		i++;
	if ((str[i] == '-' || str[i] == '+') && str[i])
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i] - 48);
		if (0 > res && sign == -1)
			return (0);
		else if (0 > res && sign == 1)
			return (-1);
		i++;
	}
	return (sign * res);
}

void	cleanup(t_smplcmd *cmdlst, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	free_list(&cmdlst);
}

int	check_digit(char *s)
{
	int	i;

	if (!(*s))
		return (0);
	i = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			while (s[i] && s[i] == ' ')
				i++;
			if (s[i] != '\0')
				return (0);
			return (1);
		}
		i++;
	}
	return (1);
}

int	ch_exit(char **args)
{
	int	i;

	i = envp_len(args);
	if (args[1] && !check_digit(args[1]))
	{
		(write(2, "exit: ", 6), write(2, args[1], ft_strlen(args[1])));
		write (2, ": numeric argument required\n", 29);
		return (255);
	}
	if (i > 2 && check_digit(args[1]))
		return (write(2, "exit: too many arguments\n", 25), 1);
	else if (i == 1)
		return (0);
	else if (i == 2 && check_digit(args[1]))
		return (ft_atoi(args[1]));
	return (0);
}

int	ft_exit(t_smplcmd *cmdlst, char **args, char **envp)
{
	int		i;

	i = envp_len(args);
	write(2, "exit\n", 5);
	if (args[1] && !check_digit(args[1]))
	{
		write(2, "exit: ", 6);
		write(2, args[1], ft_strlen(args[1]));
		write (2, ": numeric argument required\n", 29);
		cleanup(cmdlst, envp);
		exit(255);
	}
	if (i > 2 && check_digit(args[1]))
		return (write(2, "exit: too many arguments\n", 25), 1);
	else if (i == 1)
	{
		cleanup(cmdlst, envp);
		exit(0);
	}
	else if (i == 2 && check_digit(args[1]))
	{
		i = ft_atoi(args[1]);
		(cleanup(cmdlst, envp), exit(i));
	}
	return (0);
}
