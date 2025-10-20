NAME = minishell_test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_TOKEN = create_token.c \
            handle_quotes.c \
            handle_quotes_2.c \
            token_pipe_utils.c \
            token_redir_utils.c \
            token_utils.c \

SRC_EXPAND = expand_utils.c \
             expand_symb_utils.c \
             expand_var_utils.c \
             expand_exit_code.c \
             expand_libft_modifs.c \
             expand.c \

SRC_OTHER = minishell.c \
            error_handling.c \
            error_wrappers.c \
            libft_utils.c \
            utils.c \

TOKEN_DIR = tokenization
EXPAND_DIR = expansion

OBJ_DIR = obj
OBJ_TOKEN  = $(addprefix $(OBJ_DIR)/$(TOKEN_DIR)/,$(SRC_TOKEN:.c=.o))
OBJ_EXPAND = $(addprefix $(OBJ_DIR)/$(EXPAND_DIR)/,$(SRC_EXPAND:.c=.o))
OBJ_OTHER  = $(addprefix $(OBJ_DIR)/,$(SRC_OTHER:.c=.o))
OBJ = $(OBJ_TOKEN) $(OBJ_EXPAND) $(OBJ_OTHER)

INCLUDES = -I .
READLINE_INC = -I /opt/homebrew/opt/readline/include
READLINE_LIB = -L /opt/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE_LIB) -o $(NAME)

$(OBJ_DIR)/$(TOKEN_DIR)/%.o: $(TOKEN_DIR)/%.c | $(OBJ_DIR)/$(TOKEN_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

$(OBJ_DIR)/$(EXPAND_DIR)/%.o: $(EXPAND_DIR)/%.c | $(OBJ_DIR)/$(EXPAND_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/$(TOKEN_DIR):
	mkdir -p $(OBJ_DIR)/$(TOKEN_DIR)

$(OBJ_DIR)/$(EXPAND_DIR):
	mkdir -p $(OBJ_DIR)/$(EXPAND_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


