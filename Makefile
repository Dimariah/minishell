NAME		=	minishell
SRCS		=	minishell.c expd.c expd_utils.c lib_tools.c
OBJS		=	$(SRCS:.c=.o)
CC			= cc -Werror -Wall -Wextra

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $^ -lreadline -o $@
	
clean	:
	@rm -f $(OBJS)

fclean	:	clean
	@rm -f $(NAME)