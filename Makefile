NAME		=	minishell
SRCS		=	minishell.c expd.c expd_utils.c
OBJS		=	$(SRCS:.c=.o)
CC			= cc -Werror -Wall -Wextra

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $^ -lreadline -o $@
	
clean	:
	@rm -f $(OBJS)