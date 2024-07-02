/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messkely <messkely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:34:20 by messkely          #+#    #+#             */
/*   Updated: 2024/07/02 03:34:33 by messkely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_prompt_list(t_prompt *head)
{
	t_prompt	*current;
	int			i;

	current = head;
	while (current)
	{
		printf("Node:\n");
		i = 0;
		while (current->argv && current->argv[i])
		{
			printf("argv[%d]: %s\n", i, current->argv[i]);
			i++;
		}
		i = 0;
		while (current->file && current->file[i])
		{
			printf("file[%d]: %s\n", i, current->file[i]);
			i++;
		}
		printf("########################\n");
		current = current->next;
	}
}

void	ft_parser(t_prompt *pmp)
{
	char	**arr;
	char	*input;
	char	*trimmed_input;
	int		i;

	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		trimmed_input = ft_strtrim(input, " ");
		free(input);
		if (check_syntax(trimmed_input))
			continue ;
		arr = process_token(trimmed_input, '|');
		if (!arr)
			continue ;
		i = 0;
		while (arr[i])
			ft_add_back(&pmp, ft_lstnew(arr[i++]));
		print_prompt_list(pmp);
		ft_broom(arr);
	}
}

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_prompt	*prompt;

	prompt = NULL;
	atexit(f);
	(void)ac;
	(void)av;
	(void)env;
	ft_parser(prompt);
	free_list(prompt);
	return (0);
}

//  cat > file1 | echo > file2
