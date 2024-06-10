/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:16:09 by yiken             #+#    #+#             */
/*   Updated: 2024/06/10 12:04:15 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

char	*expd_line(char **envp, char *str);

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*expded_line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (perror("readline"), 1);
		if (*line)
			add_history(line);
		expded_line = expd_line(envp, line);
		if (!expded_line)
			continue ;
		printf("%s\n", expded_line);
		free(expded_line);
	}
}
