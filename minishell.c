/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiken <yiken@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:16:09 by yiken             #+#    #+#             */
/*   Updated: 2024/06/07 21:11:37 by yiken            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <libc.h>

char	*expd_line(char **envp, char *str);

void	leaks()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	*expded_line;
	atexit(leaks);
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			return (perror("readline"), 1);
		expded_line = expd_line(envp, line);
		printf("%s\n", expded_line);
		exit(0);
	}
}
