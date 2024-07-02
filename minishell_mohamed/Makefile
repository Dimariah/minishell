NAME 	= minishell
CC		= cc
FLAGS	= -Wall -Wextra -Werror
LDFLAGS	= -lreadline
SRC		= src/minishell.c src/syntax_err.c src/parser.c src/linked_list_utils.c src/rm_parser.c
OBJ 	= $(SRC:.c=.o)
RM		= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LDFLAGS) libftt/libft.a

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean