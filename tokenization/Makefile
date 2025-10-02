NAME = minishell_test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = create_token.c \
      error_handling.c \
      error_wrappers.c \
      handle_quotes.c \
      handle_quotes_2.c \
      libft_utils.c \
      token_pipe_utils.c \
      token_redir_utils.c \
      token_utils.c \
      expand_utils.c \
      expand_symb_utils.c \
      expand_var_utils.c \
      minishell.c \

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

INCLUDES = -I .

READLINE_INC = -I /opt/homebrew/opt/readline/include
READLINE_LIB = -L /opt/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_LIB) -o $(NAME)

$(OBJ_DIR)/%.o: %.c tokenization.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

