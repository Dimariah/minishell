/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:54:43 by messkely          #+#    #+#             */
/*   Updated: 2024/07/09 15:44:44 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*add_space_in_red_cp(char *s, char *new_s,
	int double_quote, int single_quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		toggle_quotes(s[i], &single_quote, &double_quote);
		if ((s[i] == '<' || s[i] == '>') && !single_quote && !double_quote)
		{
			if (i > 0 && !ft_isspace(s[i - 1]))
				new_s[j++] = ' ';
			new_s[j++] = s[i];
			if ((s[i] == '<' || s[i] == '>') && s[i + 1] == s[i])
				new_s[j++] = s[i++];
			if (s[i + 1] && !ft_isspace(s[i + 1]))
				new_s[j++] = ' ';
		}
		else
			new_s[j++] = s[i];
		i++;
	}
	return (free(s), new_s[j] = '\0', new_s);
}

char	*add_space_in_red(char *s)
{
	int		double_quote;
	int		single_quote;
	char	*new_s;

	double_quote = 0;
	single_quote = 0;
	if (!s)
		return (NULL);
	new_s = malloc(ft_strlen(s) * 2 + 1);
	if (!new_s)
		return (free(s), NULL);
	return (add_space_in_red_cp(s, new_s, double_quote, single_quote));
}

char	**process_token_cp(char *s, char token, char **av, int tok_count)
{
	static int	i;
	int			single_quote;
	int			double_quote;
	int			start;

	single_quote = 0;
	double_quote = 0;
	start = 0;
	while (s[i])
	{
		toggle_quotes(s[i], &single_quote, &double_quote);
		if ((s[i] == token) && !single_quote && !double_quote)
		{
			if (i > start)
				av[tok_count++] = ft_strndup(s + start, i - start);
			while (s[i] == token)
				i++;
			start = i;
		}
		else
			i++;
	}
	if (start < i)
		av[tok_count++] = ft_strndup(s + start, i - start);
	return (i = 0, av[tok_count] = NULL, av);
}

char	**process_token(char *s, char token)
{
	int		tok_count;
	char	**av;

	tok_count = 0;
	av = malloc((ft_strlen(s) / 2 + 2) * sizeof(char *));
	if (!av)
	{
		free(s);
		exit(1);
	}
	return (process_token_cp(s, token, av, tok_count));
}

void	ft_parser(t_smplcmd **pmp, char *input)
{
	char	**arr;
	int		i;

	arr = process_token(input, '|');
	i = 0;
	while (arr[i])
		ft_add_back(pmp, ft_lstnew(arr[i++], arr, pmp));
	free(input);
	ft_broom(arr);
}
