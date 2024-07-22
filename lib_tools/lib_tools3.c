/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 15:00:41 by messkely          #+#    #+#             */
/*   Updated: 2024/07/22 00:02:20 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(char *s, size_t n)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = ft_strlen(s);
	if (n > len)
		n = len;
	new_str = (char *)malloc(n + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[n] = '\0';
	return (new_str);
}

int	ft_arglen(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	exit_status(int exit_status)
{
	static int	value;

	if (exit_status != -500)
		value = exit_status;
	return (value);
}

char	*check_dollar(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if (str[i] != '$')
		return (str);
	tmp = malloc(ft_strlen(str) + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[i] = '\0';
	// free(str);
	return (tmp);
}

void	check_heredoc_quotes(char **args, t_smplcmd *cmd)
{
	int i;

	cmd->exp_herd = 0;
	if (args == NULL)
		return ;
	i = 0;
	while (args[i] != NULL)
	{
		if (strcmp(args[i], "<<") == 0)
		{
			i++;
			if (args[i][0] == '"' || args[i][0] == '\'')
			{
				cmd->exp_herd = 1;
				printf("I find It\n");
				return;
			}
		}
		i++;
	}
	cmd->exp_herd = 0;
}
