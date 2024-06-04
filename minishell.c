#include <readline/readline.h>
#include <libc.h>

char	*expd_str(char **envp, char *str);

int main(int ac, char **av, char **envp)
{
	char	*str;
	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
			return (perror("readline"), 1);
		printf("%s\n", expd_str(envp, str));
	}
}