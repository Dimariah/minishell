/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 11:23:48 by yiken             #+#    #+#             */
/*   Updated: 2024/07/10 16:10:27 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strlen(char *str);

int	unset_kerror(char *key, int err_print)
{
	int	i;

	i = 0;
	while (i == 0 || key[i])
	{
		if ((i == 0 && !key[i]) || (i == 0 && (key[i] >= '0' && key[i] <= '9'))
			|| ((key[i] < 'a' || key[i] > 'z') && (key[i] < '0' || key[i] > '9')
				&& (key[i] < 'A' || key[i] > 'Z') && key[i] != '_'))
		{
			if (err_print)
			{
				write(2, "unset: `", 8);
				write(2, key, ft_strlen(key));
				write(2, "\': not a valid identifier\n", 26);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	ch_unset(t_smplcmd *cmdlst)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmdlst->argv[i])
	{
		if (unset_kerror(cmdlst->argv[i], 1))
			status = 1;
		i++;
	}
	return (status);
}

void	envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}
