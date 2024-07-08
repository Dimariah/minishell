/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:10:26 by messkely          #+#    #+#             */
/*   Updated: 2024/07/07 19:09:20 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	toggle_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && !(*double_quote))
		*single_quote = !(*single_quote);
	else if (c == '"' && !(*single_quote))
		*double_quote = !(*double_quote);
}

char	*rm_escape_char(char *s)
{
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;
	char	*res;

	single_quote = 0;
	double_quote = 0;
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		exit(1);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			res[j++] = s[i];
		i++;
	}
	return (res[j] = '\0', free(s), res);
}

static int	count_valid_elements(char *args[], int n)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0
			|| ft_strcmp(args[i], ">>") == 0 || ft_strcmp(args[i], "<<") == 0)
			i++;
		else
			count++;
		i++;
	}
	return (count);
}

char	**rm_red_args_cp(char **args, t_smplcmd *pmp, char **new_args)
{
	int		i;
	int		j;
	int		file_index;

	j = 0;
	i = 0;
	file_index = 0;
	while (args[i])
	{
		if (!ft_strcmp(args[i], ">") || !ft_strcmp(args[i], "<")
			|| !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
		{
			pmp->reds[file_index++] = ft_strdup(args[i]);
			if (args[i + 1])
				pmp->reds[file_index++] = ft_strdup(args[++i]);
		}
		else
			new_args[j++] = ft_strdup(args[i]);
		i++;
	}
	ft_broom(args);
	return (new_args[j] = NULL, pmp->reds[file_index] = NULL, new_args);
}

char	**rm_red_args(char **args, int n, t_smplcmd *pmp)
{
	char	**new_args;
	int		new_size;

	new_size = count_valid_elements(args, n);
	new_args = malloc((new_size + 1) * sizeof(char *));
	if (!new_args)
		exit(1);
	pmp->reds = malloc((n - new_size + 1) * sizeof(char *));
	if (!pmp->reds)
		return (ft_broom(new_args), NULL);
	return (rm_red_args_cp(args, pmp, new_args));
}
