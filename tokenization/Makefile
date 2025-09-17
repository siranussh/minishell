NAME = minishell_test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = create_token.c \
      error_handling.c \
      handle_quotes.c \
      handle_quotes_2.c \
      libft_utils.c \
      redirection_utils.c \
      token_utils.c \

OBJ = $(SRC:.c=.o)

INCLUDES = -I .

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c tokenization.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
