/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:15:54 by messkely          #+#    #+#             */
/*   Updated: 2024/07/08 10:26:58 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *s, char c)
{
	if (c == ' ' || c == '\0')
		printf("minishell: %s newline\n", s);
	else
		printf("minishell: %s `%c'\n", s, c);
}

static int	check_multi_pipe(char *s)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	if (s[i] == '|')
		return (printf("syntax error near unexpected token `|'\n"), 1);
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if (s[i] == '|' && !double_quote && !single_quote)
		{
			while (s[++i] && ft_isspace(s[i]))
				i++;
			if (s[i] == '|')
				return (printf("syntax error near unexpected token `|'\n"), 1);
		}
		i++;
	}
	return (0);
}

static int	check_red_pattern(char *s, int *i)
{
	int	j;

	j = *i;
	if (s[j] == '<' && s[j + 1] == '<')
		j += 2;
	else if (s[j] == '>' && s[j + 1] == '>')
		j += 2;
	else if (s[j] == '<' || s[j] == '>')
		j++;
	else
		return (0);
	while (s[j] && s[j] == ' ')
		j++;
	if (s[j] == '|')
		return (0);
	if (!s[j] || (s[j] == '<' || s[j] == '>'))
		return (0);
	*i = j - 1;
	return (1);
}

static int	check_syntax_red(char *s)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (s[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if ((s[i] == '<' || s[i] == '>') && !single_quote && !double_quote)
		{
			if (!check_red_pattern(s, &i))
			{
				ft_error("syntax error near unexpected token", s[i + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_syntax(char *input)
{
	if (*input == 0)
		return (0);
	if (check_multi_pipe(input) || check_syntax_red(input))
		return (free(input), 1);
	return (0);
}
// danger :  cat >> jdjd >> jdjd >> jdjd < shiva >> jdjd << shiva ">>" jdjd