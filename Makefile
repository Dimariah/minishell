NAME 	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lreadline
SRC		= buins/cd.c buins/echo.c buins/env.c buins/exit.c buins/export.c buins/export_extras.c buins/export_utils.c buins/pwd.c \
		buins/unset.c buins/unset_utils.c executor/exec.c executor/exec_buin.c executor/handle_reds.c executor/xpath_get.c expander/code_expd.c \
		expander/expd.c expander/expd_utils.c lib_tools/lib_tools.c lib_tools/lib_tools1.c lib_tools/lib_tools2.c lib_tools/lib_tools3.c \
		parser/linked_list_utils.c parser/parser.c parser/rm_parser.c minishell.c syntax_err.c
OBJ 	= $(SRC:.c=.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean